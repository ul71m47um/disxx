#!/usr/bin/ruby

require "rbconfig"

if $0 == __FILE__
	puts RbConfig::CONFIG["rubyhdrdir"]
end
