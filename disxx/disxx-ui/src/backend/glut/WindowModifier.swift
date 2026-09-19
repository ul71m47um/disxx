import AppKit

public class WinMod
{
	public static func modify() -> Void
	{
		DispatchQueue.main.async
		{
			if let window: NSWindow = NSApp.windows.first(where: { NSStringFromClass(type(of: $0)) == "GLUTWindow" })
			{
				window.styleMask.insert(.closable)
				if let button: NSButton = window.standardWindowButton(.closeButton)
				{
					button.isHidden = false
					button.isEnabled = true
				}

				window.displayIfNeeded()
			}
		}
	}
}
