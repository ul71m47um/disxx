#!/usr/bin/ruby

require "rbconfig"
require "optparse"

if $0 == __FILE__
	OptionParser.new do |opts|
		options.banner = "Usage: ruby config.rb [options]"
		
		opts.on "-c", "--cflags", "C/C++ compiler flags for files that include Ruby headers" do
			puts "-I#{RbConfig::CONFIG["rubyhdrdir"]}"
		end

		opts.on "-l --ldflags", "Display path to Ruby shared library" do
			puts "-L#{RbConfig::CONFIG["libdir"]}"
		end
	end
end
