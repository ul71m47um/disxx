#!/usr/bin/ruby

require "rbconfig"
require "optparse"

if $0 == __FILE__
	options = Hash::new
	OptionParser::new do |opts|
		opts.banner = "Usage: ruby config.rb [options]"
		
		opts.on "-c", "--cflags", "C/C++ compiler flags for files that include Ruby headers" do |c|
			options[:cflags] = c
		end

		opts.on "-l", "--ldflags", "Display linker flags" do |l|
			options[:ldflags] = l
		end

		opts.on "-h", "--help", "Display a summary of config.rb arguments" do |_|
			puts opts
		end
	end.parse!

	if options[:cflags]
		puts "-I#{RbConfig::CONFIG["rubyhdrdir"]}"
	elsif options[:ldflags]
		puts <<~EOF.gsub /\n/, ' '
			-L#{RbConfig::CONFIG["libdir"]}
			#{
				RbConfig::CONFIG["LIBRUBY_SO"]
					.gsub(/\Alib/, '-l')
					.gsub(/\.((dylib)|(so)|(dll))$/, '')
			}
		EOF
	end
end
