module;

#define MKHEX(x) (std::format("{:#x}", (x)))

module Application;

import disxx.utility.error.NullPointerError;
import disxx.utility.ini.Parser;

import disxx.loader.executable.ExecutableFile;
import disxx.loader.macho.Loader;

import disxx.disasm.Disassembler;
import disxx.disasm.Printer;

import disxx.ui.backend.glut.Context;
import disxx.ui.SourceEditor;
import disxx.ui.MessageBox;
import disxx.ui.TabbedPane;
import disxx.ui.MainWindow;
import disxx.ui.TextInput;
import disxx.ui.MenuBar;
import disxx.ui.Widget;
import disxx.ui.Button;
import disxx.ui.Label;
import disxx.ui.Frame;

import ScriptWindow;
import DisLog;

import std;

// Miscellaneous function(s)
namespace
{
	inline std::tuple<std::string, std::string, std::string> splitver(const std::string &version) noexcept
	{
		std::smatch groups{};
		std::regex_match(version, groups, std::regex{R"(^(\d+)\.(\d+)\.(\d+)$)"});
		// Return major minor and patchlevel strings
		return std::make_tuple(groups[1], groups[2], groups[3]);
	}
}

// The only one instance
Application *Application::s_pInstance{nullptr};

Application::Application(void) noexcept
	: m_Window{disxx::ui::utility::Vec2<int>{400, 300}, "dis++ - Main menu"}
	, m_pLabels{nullptr}
	, m_pTabs{nullptr}
	, m_ModalWidgets{}
	, m_ScriptWindows{}
	, m_Logger{}
	, m_bActiveModal{false}
{
	this->m_pTabs = nullptr;
	this->m_pLabels = nullptr;
	this->m_Window.SetVisible(true);

	{
		disxx::ui::Button open{5.f, 250.f, 75.f, 25.f};
		open.SetColor(0.3f, 0.3f, 0.3f);
		open.SetText("Open");
		open.SetCallback
		(
			disxx::ui::Button::Trigger::BTN_CLICKED,
			[this](const disxx::ui::Widget *const) -> void
			{
				disxx::ui::Frame frame{0.f, 0.f, 400.f, 300.f};
				frame.SetColor(0.2f, 0.2f, 0.2f);
				this->m_Window.AddWidget(std::make_unique<disxx::ui::Frame>(frame));

				disxx::ui::Label upper
				{
					200.f,
					250.f,
					0.f,
					0.f
				};
				upper.SetColor(1.f, 1.f, 1.f);
				upper.SetText("Select an executable to disassemble");
				this->m_Window.AddWidget(std::make_unique<disxx::ui::Label>(upper));
				
				disxx::ui::Label label
				{
					75.f,
					195.f,
					0.f,
					0.f
				};
				label.SetColor(0.3f, 0.3f, 0.3f);
				label.SetText("Executable:");
				this->m_Window.AddWidget(std::make_unique<disxx::ui::Label>(label));

				disxx::ui::TextInput input
				{
					400 / 3.f,
					175.f,
					250.f,
					40.f
				};
				input.SetColor(0.3f, 0.3f, 0.3f);
				this->m_Window.AddWidget(std::make_unique<disxx::ui::TextInput>(input));

				auto &ref
				{
					dynamic_cast<disxx::ui::TextInput &>
					(
						**this
							->m_Window
							.GetWidgets()
							.rbegin()
					)
				};
	
				disxx::ui::Button ok{150.f, 100.f, 100.f, 40.f};
				ok.SetColor(0.3f, 0.3f, 0.3f);
				ok.SetText("OK");
				ok.SetCallback
				(
					disxx::ui::Button::Trigger::BTN_CLICKED,
					[this, &ref](const disxx::ui::Widget *const) mutable -> void
					{
						if (std::error_code errc{}; std::filesystem::exists(ref.GetText(), errc)) [[likely]]
							this->Setup(ref.GetText());
						else
						{
							ref.SetText(std::string{});
							//disxx::ui::MessageBox box{"Unable to open the file"};
							//box.Exec();
						}
					}
				);
				this->m_Window.AddWidget(std::make_unique<disxx::ui::Button>(ok));
			}
		);
		this->m_Window.AddWidget(std::make_unique<disxx::ui::Button>(open));
	}

	{
		disxx::ui::Label text{240.f, 260.f, 0.f, 0.f};
		text.SetColor(1.f, 1.f, 1.f);
		text.SetText("Select an executable to disassemble");
		this->m_Window.AddWidget(std::make_unique<disxx::ui::Label>(text));
	}

	{
		disxx::ui::Button pass{5.f, 210.f, 75.f, 25.f};
		pass.SetColor(0.3f, 0.3f, 0.3f);
		pass.SetText("Pass");
		pass.SetCallback
		(
			disxx::ui::Button::Trigger::BTN_CLICKED,
			[this](const disxx::ui::Widget *const) -> void
			{ this->Setup(std::filesystem::path{}); }
		);
		this->m_Window.AddWidget(std::make_unique<disxx::ui::Button>(pass));
	}

	{
		disxx::ui::Label text{225.f, 215.f, 0.f, 0.f};
		text.SetColor(1.f, 1.f, 1.f);
		text.SetText("Continue without opening a file");
		this->m_Window.AddWidget(std::make_unique<disxx::ui::Label>(text));
	}
}

void Application::LoadLabels(const std::filesystem::path &path) noexcept
{
	if (!this->m_pLabels) [[unlikely]]
		return;

	auto &labels{*this->m_pLabels};
	labels.ClearText();

	disxx::loader::macho::Loader ldr{};
	if (!ldr.LoadFile(path)) [[unlikely]]
		return;

	const auto dataResult{ldr.LoadData()};
	if (!dataResult) [[unlikely]]
		return;

	for (const auto &section : dataResult->GetSections())
	{
		for (const auto &label : section.GetLabels())
		{
			labels.AddLine
			(
				"<color value=\"0.7 0.6 0.2 1.0\">{}</color>:"
				"<color value=\"0.8 0.6 0.2 1.0\">{:#016}</color>:"
				"<color value=\"0.6 0.6 0.2 1.0\">{}</color>",
				section.GetName(),
				label.GetAddress(),
				label.GetName()
			);
		}
	}

	const auto [width, height]{s_pInstance->m_Window.GetSize()};
	labels.Resize
	(
		disxx::ui::utility::Vec2<float>
		{
			static_cast<float>(width),
			static_cast<float>(height) * 0.2f
		}
	);
}

void Application::Disassemble(const std::filesystem::path &path) noexcept
{
	this->LoadLabels(path);

	disxx::ui::SourceEditor editor{};
	editor.SetColor(0.2f, 0.2f, 0.2f);
	editor.AddLine(";{:*<64}", "");
   	editor.AddLine(";  This file was generated by the dis++ disassembler");
   	editor.AddLine(";\tCopyright (C) ultimatum");
   	editor.AddLine(";  Dis++ version: 0.3.0 - {}", path.string());
   	editor.AddLine(";{:*<64}", "");
   	editor.AddLine("");
   	editor.AddLine(";{:=<63};", "");
	editor.AddLine("");

	// Load the executable
    disxx::loader::macho::Loader ldr{};
	if (!ldr.LoadFile(path)) [[unlikely]]
		return;
	
	// Load metadata of the executable
	auto metadataResult{ldr.LoadMetadata()};
	if (!metadataResult) [[unlikely]]
		return;

	editor.AddLine(";{:*<28}METADATA{:*<28}", "", "");
	editor.AddLine(";  File path: {}", path.string());
	editor.AddLine(";  File type: Mach-O {}", ldr.GetFileType());	
	editor.AddLine(";  Target OS: {}, v{}", metadataResult->GetPlatformName(), metadataResult->GetPlatformMinVersion());
	const auto &_
	{
		ldr
			.LoadImageBase()
			.and_then
			(
				[&editor](const auto &addr) -> std::optional<long long int>
				{ 
					editor.AddLine(";\tImage base: {}", MKHEX(addr));
					return addr;
				}
			).or_else
			(
				[&editor] -> std::optional<long long int>
				{
					editor.AddLine("\tImage base: unknown");
					return std::nullopt; 
				}
			)
	};
	
	for (const auto &[name, version] : metadataResult->GetBuildTools())
		editor.AddLine(";  Build tool: {}, v{}", name, version);
	editor.AddLine(";{:*<64}", "");
	editor.AddLine("");

	const auto &[platformMajor, platformMinor, _]{::splitver(metadataResult->GetPlatformMinVersion())};
	const auto &[sdkMajor, sdkMinor, _]{::splitver(metadataResult->GetSDKVersion())};
	editor.AddLine
	(
		"<color value=\"0.6 0.6 0.2 1.0\">.build_version</color>"
		" {}, <color value=\"0.7 0.2 0.1 1.0\">{}</color>,"
		" <color value=\"0.7 0.2 0.1 1.0\">{}</color>"
		" sdk_version <color value=\"0.7 0.2 0.1 1.0\">{}</color>,"
		" <color value=\"0.7 0.2 0.1 1.0\">{}</color>",
		metadataResult->GetPlatformName()
			| std::views::all
			| std::views::transform([](auto ch) -> char { return static_cast<char>(std::tolower(ch)); })
			| std::ranges::to<std::string>(),
		platformMajor,
		platformMinor,
		sdkMajor,
		sdkMinor
	);

	const auto dataResult{ldr.LoadData()};
	if (!dataResult) [[unlikely]]
		return;

	for (auto &section : dataResult->GetSections())
	{
		const auto name{section.GetName()};
		editor.AddLine("");
		editor.AddLine("<color value=\"0.6 0.6 0.2 1.0\">.section</color> {}", name);
		editor.AddLine("");

		// these sections are considered as executable
		if (name == "__TEXT,__text" || name == "__TEXT,__stubs")
		{
    		std::unordered_map<std::uint64_t, std::string> names;
    		for (const auto &label : section.GetLabels())
    		    names[label.GetAddress()] = label.GetName();
		
			for (const auto &label : section.GetLabels())
		    {
		        editor.AddLine("<color value=\"0.6 0.6 0.2 1.0\">{}</color>:", label.GetName());

				disxx::disasm::Disassembler disasm{};
				const auto vec
				{
					label.GetData<std::uint32_t>()
						| std::views::all
						| std::views::transform([](const auto &bytes) -> auto { return disxx::disasm::Bytes{bytes}; })
						| std::ranges::to<std::vector<disxx::disasm::Bytes>>()
				};
	   		    for (disxx::disasm::Address addr{label.GetAddress()}; const auto &bytes : vec)
    		    {
					if (const auto &insn{disasm.Disassemble(bytes, addr++)}) [[likely]]
					{
						auto mnemonic
						{
							[&insn] -> std::string
							{
								std::string str{};
								disxx::disasm::Printer<std::back_insert_iterator<std::string>> printer{std::back_inserter(str)};
								printer.Print(*insn);
					
								const std::regex imms{R"(#-?((0x[a-f0-9]+)|(\d+\.\d+)))"};
								for (std::sregex_iterator it{str.begin(), str.end(), imms}, end{}; it != end; ++it)
								{
									#pragma clang diagnostic push
									#pragma clang diagnostic ignored "-Wsign-conversion"
									if (const auto prev{str.at(it->position() - 1uz)}; prev == '>') [[unlikely]]
									#pragma clang diagnostic pop
										continue;
				
									// Check if it's a pc-relevant address (using .value_or(0) instead of .value() method)
									if (const auto insnAddr{insn->GetProgramCounterRelevantAddress()}; insnAddr && std::string{"#"} + MKHEX(insnAddr.value_or(0)) == it->str())
									{
										str = std::regex_replace
										(
											str,
											std::regex{it->str()},
											std::format("<color value=\"0.6 0.6 0.2 1.0\">{}</color>", it->str())
										);
									}
									else
									{
										str = std::regex_replace
										(
											str,
											std::regex{it->str()},
											std::format("<color value=\"0.7 0.2 0.1 1.0\">{}</color>", it->str())
										);
									}

									it = std::sregex_iterator{str.begin(), str.end(), imms};
								}

								const std::regex regs{R"(((b|h|s|d|q|v|w|x)\d{1,2})|(((ws)|s)p)|((w|x)zr))"};
								for (std::sregex_iterator it{str.begin(), str.end(), regs}, end{}; it != end; ++it)
								{
									// Check if it was accidentally confused with immediate operand
									#pragma clang diagnostic push
									#pragma clang diagnostic ignored "-Wsign-conversion"
									if (const auto prev{str.at(it->position() - 1uz)}; prev == 'x' || std::isdigit(prev) || (prev >= 97 && prev <= 102) || prev == '>') [[unlikely]]
									#pragma clang diagnostic pop
										continue;
									// Check if a number of the register is valid
									#pragma clang diagnostic push
									#pragma clang diagnostic ignored "-Wunsafe-buffer-usage"
									else if (auto n{0ull}; std::from_chars(it->str().data() + 1, it->str().data() + it->str().size() - 1, n)) [[likely]]
										if (n > 31) [[unlikely]]
											continue;
									#pragma clang diagnostic pop

									str = std::regex_replace
									(
										str,
										std::regex{it->str()},
										std::format("<color value=\"0.3 0.7 0.7 1.0\">{}</color>", it->str())
									);

									it = std::sregex_iterator{str.begin(), str.end(), regs};
								}
								
								return str;
							}()
						};

						if (auto insnAddr{insn->GetProgramCounterRelevantAddress()})
    		        	{
							#pragma clang diagnostic push
							#pragma clang diagnostic ignored "-Wsign-conversion"
    		            	if (auto it{names.find(*insnAddr)}; it != names.end())
    		            	#pragma clang diagnostic pop
							{
    		            	    editor.AddLine
    		            	    (
									"<color value=\"0.7 0.7 0.7 1.0\">|</color>\t{}\t\t"
									"<color value=\"0.7 0.7 0.7 1.0\">; {:#x}</color>",
    		            	        std::regex_replace
									(
										mnemonic,
										std::regex
										{
											std::string{"#"}
												+ MKHEX(*insnAddr)
										},
										it->second
									),
									label.GetAddress()
								);
	   		            	    
								continue;
	   		            	}
	   		        	}

						editor.AddLine("<color value=\"0.7 0.7 0.7 1.0\">|</color>\t{}", mnemonic);
					}
					else
						editor.AddLine("<color value=\"0.7 0.7 0.7 1.0\">|</color>\t{}", insn.error().what());
				}
    		}
		}
		else
		{
			for (const auto &label : section.GetLabels())
			{
				editor.AddLine("<color value=\"0.6 0.6 0.2 1.0\">{}</color>:", label.GetName());
				for (const auto &byte : label.GetData<std::uint8_t>())
				{
					editor.AddLine
					(
						"<color value=\"0.7 0.7 0.7 1.0\">|</color>"
						"\t<color value=\"0.6 0.6 0.2 1.0\">.byte </color>"
						"<color value=\"0.7 0.2 0.1 1.0\">{:#02x}</color>{}",
						byte,
						std::isprint(byte) && !std::isspace(byte)
							? std::format("\t<color value=\"0.7 0.7 0.7 1.0\">; \'{:c}\'</color>", byte)
							: std::string{}
					);
				}
			}
		}
	}

	disxx::ui::Tab tab{};
	tab.SetColor(0.2f, 0.2f, 0.2f);
	tab.SetText(path.string());
	tab.SetTextArea(std::move(editor));
	if (this->m_pTabs) [[likely]]
		this->m_pTabs->Push(std::move(tab));
}

void Application::RequestFile(std::string_view headline, std::string_view request, std::function<void(std::filesystem::path)> callback) noexcept
{
	if (this->m_bActiveModal) [[unlikely]]
		return;

	const auto [width, height]{this->m_Window.GetSize()};

	disxx::ui::Frame frame
	{
		static_cast<float>(width) / 4.f,
		static_cast<float>(height) / 4.f,
		static_cast<float>(width) / 2.f,
		static_cast<float>(height) / 2.f
	};
	frame.SetColor(0.2f, 0.2f, 0.2f);
	this->m_Window.AddWidget(std::make_unique<disxx::ui::Frame>(frame));
	this->m_ModalWidgets.emplace_back(this->m_Window.GetWidgets().rbegin()->get());

	disxx::ui::Label upper
	{
		static_cast<float>(width) / 2.f,
		static_cast<float>(height) / 2.f + 100.f,
		0.f,
		0.f
	};
	upper.SetColor(1.f, 1.f, 1.f);
	upper.SetText(headline);
	this->m_Window.AddWidget(std::make_unique<disxx::ui::Frame>(frame));
	this->m_ModalWidgets.emplace_back(this->m_Window.GetWidgets().rbegin()->get());
	
	disxx::ui::Label label
	{
		static_cast<float>(width) / 4.f + 70.f,
		static_cast<float>(height) / 2.f + 45.f,
		0.f,
		0.f
	};
	label.SetColor(0.3f, 0.3f, 0.3f);
	label.SetText(request);
	this->m_Window.AddWidget(std::make_unique<disxx::ui::Frame>(frame));
	this->m_ModalWidgets.emplace_back(this->m_Window.GetWidgets().rbegin()->get());
	s_pInstance->m_Window.AddWidget(std::make_unique<disxx::ui::Label>(label));

	disxx::ui::Button ok
	{
		static_cast<float>(width) / 2.f + static_cast<float>(width) / 5.f - 100.f,
		static_cast<float>(height) / 2.f - static_cast<float>(height) / 5.f,
		100.f,
		40.f
	};
	ok.SetColor(0.3f, 0.3f, 0.3f);
	ok.SetText("OK");
	ok.SetCallback
	(
		disxx::ui::Button::Trigger::BTN_CLICKED,
		[this, &callback](const disxx::ui::Widget *const) -> void
		{
			const auto path
			{
				dynamic_cast<disxx::ui::TextInput &>
				(
					**this
						->m_Window
						.GetWidgets()
						.rbegin()
				).GetText()
			};

			this->ClearModal();

			callback(path);
		}
	);
	this->m_Window.AddWidget(std::make_unique<disxx::ui::Frame>(frame));
	this->m_ModalWidgets.emplace_back(this->m_Window.GetWidgets().rbegin()->get());

	disxx::ui::Button cancel
	{
		static_cast<float>(width) / 2 - static_cast<float>(width) / 5.f,
		static_cast<float>(height) / 2 - static_cast<float>(height) / 5.f,
		100.f,
		40.f
	};
	cancel.SetColor(0.3f, 0.3f, 0.3f);
	cancel.SetText("Cancel");
	cancel.SetCallback
	(
		disxx::ui::Button::Trigger::BTN_CLICKED,
		[this](const disxx::ui::Widget *const) -> void
		{ this->ClearModal(); }
	);
	this->m_Window.AddWidget(std::make_unique<disxx::ui::Frame>(frame));
	this->m_ModalWidgets.emplace_back(this->m_Window.GetWidgets().rbegin()->get());

	disxx::ui::TextInput input
	{
		static_cast<float>(width) / 3.f + 50.f,
		static_cast<float>(height) / 2.f + 25.f,
		250.f,
		40.f
	};
	input.SetColor(0.3f, 0.3f, 0.3f);
	this->m_Window.AddWidget(std::make_unique<disxx::ui::Frame>(frame));
	this->m_ModalWidgets.emplace_back(this->m_Window.GetWidgets().rbegin()->get());

	this->m_bActiveModal = true;
}

void Application::ClearModal(void) noexcept
{
	for (const auto &pWidget : this->m_ModalWidgets)
		pWidget->SetVisible(false);

	const auto _
	{
		std::erase_if
		(
			this->m_Window.GetWidgets(),
			[](const auto &pWidget) -> bool
			{ return !pWidget->Visible(); }
		)
	};

	this->m_ModalWidgets.clear();
	this->m_bActiveModal = false;
}

void Application::Setup(std::filesystem::path path) noexcept
{
	this->m_Window.GetWidgets().clear();
	this->m_Window.SetSize(disxx::ui::utility::Vec2<int>{800, 600});
	this->m_Window.SetTitle("dis++ v0.4.0-beta");
	this->m_Window.SetVisible(true);
	const auto [width, height]{s_pInstance->m_Window.GetSize()};
	
	{
		disxx::ui::TabbedPane pane
		{
			0.f,
			0.f,
			static_cast<float>(width) * 1.f,
			static_cast<float>(height) * 0.7f
		};
		pane.SetColor(0.2f, 0.2f, 0.2f);
		pane.SetTabClickCallback
		(
			[this](disxx::ui::Tab &tab) -> void
			{
				// Get a file path
				const auto currentPath
				{
					std::regex_replace
					(
						tab.GetText().data(),
						std::regex{R"(\s+\-\s+hex$)"},
						""
					)
				};

				this->LoadLabels(currentPath);
			}
		);

		this->m_Window.AddWidget(std::make_unique<disxx::ui::TabbedPane>(pane));
	}

	{
		disxx::ui::SourceEditor labels
		{
			0.f,
			static_cast<float>(height) * 0.75f,
			static_cast<float>(width) * 1.f,
			static_cast<float>(height) * 0.2f
		};
		labels.SetColor(0.2f, 0.2f, 0.2f);
		
		this->m_Window.AddWidget(std::make_unique<disxx::ui::SourceEditor>(labels));
		this->m_pLabels = dynamic_cast<disxx::ui::SourceEditor *>(this->m_Window.GetWidgets().rbegin()->get());
	}

	if (!path.empty())
		this->Disassemble(path);

	disxx::ui::MenuBar menuBar{};
	
	{
		disxx::ui::Menu menu{};
		menu.SetColor(0.2f, 0.2f, 0.2f);
		menu.SetText("File");

		disxx::ui::MenuEntry open
		{
			"Open...",
			[this] -> void
			{
				this->RequestFile
				(
					"Select an executable to disassemble",
					"Executable:",
					[this](std::filesystem::path p) -> void
					{
						if (std::error_code errc{}; !std::filesystem::exists(p, errc)) [[unlikely]]
						{
							//disxx::ui::MessageBox box{"Unable to open the file"};
							//box.Exec();
							return;
						}
	
						this->Disassemble(p);
					}
				);	
			}
		};
		open.SetColor(0.2f, 0.2f, 0.2f);
		menu.Add(std::move(open));

		disxx::ui::MenuEntry close
		{
			"Close",
			[this] -> void
			{
				if (!this->m_pTabs) [[unlikely]]
					return;

				const auto currentTab{this->m_pTabs->GetActiveTab()};
				if (!currentTab) [[unlikely]]
					return;

				// Get a file path
				const auto currentPath
				{
					std::regex_replace
					(
						currentTab->get().GetText().data(),
						std::regex{R"(\s+\-\s+hex$)"},
						""
					)
				};

				std::erase_if
				(
					this->m_pTabs->GetTabs(),
					[currentPath](const auto &tab) -> bool
					{
						return std::regex_search
						(
							tab.GetText().data(),
							std::regex{currentPath}
						);
					}
				);
			}
		};
		close.SetColor(0.2f, 0.2f, 0.2f);
		menu.Add(std::move(close));

		disxx::ui::MenuEntry save
		{
			"Save source",
			[this, path] -> void
			{
				if (!this->m_pTabs) [[unlikely]]
					return;

				const auto currentTab{this->m_pTabs->GetActiveTab()};
				if (!currentTab) [[unlikely]]
					return;

				std::fstream file{path, std::fstream::out | std::fstream::binary | std::fstream::trunc};
                if (!file.is_open()) [[unlikely]]
                {
                	disxx::ui::MessageBox box{"Unable to open the file"};
                    //box.Exec();
                    return;
                }

                const auto area{currentTab->get().GetTextArea()};
                for (const auto &line : area.GetLines())
                	for (const auto &ch : std::regex_replace(line, std::regex{R"(\|)"}, "") + "\n")
                    	file.write(&ch, sizeof(char));
			}
		};
		save.SetColor(0.2f, 0.2f, 0.2f);
		menu.Add(std::move(save));

		disxx::ui::MenuEntry script
		{
			"Script",
			[this] -> void
			{
				this->RequestFile
				(
					"Load script file",
					"Path:",
					[this](std::filesystem::path p) -> void
					{
						if (std::error_code errc{}; !std::filesystem::exists(p, errc)) [[unlikely]]
                        {
                            //disxx::ui::MessageBox box{"Unable to open the file"};
                            //box.Exec();
                            return;
                        }
                           
						this->m_ScriptWindows.emplace_back(ScriptWindow{p});
					}
				);
			}
		};
		script.SetColor(0.2f, 0.2f, 0.2f);
		menu.Add(std::move(script));

		disxx::ui::MenuEntry exit
		{
			"Exit",
			[] -> void { std::exit(0); }
		};
		exit.SetColor(0.2f, 0.2f, 0.2f);
		menu.Add(std::move(exit));

		menuBar.Add(std::move(menu));
	}

	{
		disxx::ui::Menu menu{};
		menu.SetColor(0.2f, 0.2f, 0.2f);
        menu.SetText("View");

		disxx::ui::MenuEntry hex
		{
			"Hex",
			[this] -> void
			{
				if (!this->m_pTabs) [[unlikely]]
                    return;

                const auto currentTab{this->m_pTabs->GetActiveTab()};
                if (!currentTab) [[unlikely]]
                    return;

                const auto currentPath
                {
                    std::regex_replace
                    (
                        currentTab->get().GetText().data(),
                        std::regex{R"(\s\-\shex)"},
                        ""
                    )
                };

                for (const auto &tab : this->m_pTabs->GetTabs())
                    if (tab.GetText() == currentPath + " - hex") [[unlikely]]
                        return;

                disxx::ui::Tab tab{};
                tab.SetColor(0.2f, 0.2f, 0.2f);
                std::string fmt{currentPath + " - hex"};
                tab.SetText(fmt);

                std::fstream file{currentPath, std::fstream::binary | std::fstream::in};
                if (!file.is_open()) [[unlikely]]
                {
                    //disxx::ui::MessageBox box{"Unable to open the file"};
                    //box.Exec();
                    return;
                }

                disxx::ui::SourceEditor src{};
                for (unsigned long long int addr{0ull}; !file.eof(); addr += 8ull)
                {
                    std::string str{};
                    for (auto i{0}; i < 8 && !file.eof(); ++i)
                    {
                        char byte{};
                        file.read(&byte, sizeof(byte));
                        str += std::format("{:#02x} ", byte);
                    }

                    src.AddLine("{:#016x}: {}", addr, str);
                }

                tab.SetTextArea(std::move(src));
                this->m_pTabs->Push(std::move(tab));
			}
		};
		hex.SetColor(0.2f, 0.2f, 0.2f);
		menu.Add(std::move(hex));

		menuBar.Add(std::move(menu));
	}

	s_pInstance->m_Window.AddWidget(std::make_unique<disxx::ui::MenuBar>(menuBar));
}

int Application::Exec(void) noexcept { return this->m_Window.Exec(); }
