#! /usr/bin/env ruby
require 'rake'
require 'rake/clean'

CC      = 'clang'
CFLAGS  = "-Wall -Werror-implicit-function-declaration -Wno-format -std=gnu11 -Iinclude #{ENV['CFLAGS']}"
LDFLAGS = "#{ENV['LDFLAGS']}"

# CFLAGS << '-D BASE_KEY=VK_MENU'

SOURCES = FileList['source/**/*.c']
OBJECTS = SOURCES.ext ?o

CLEAN.include   OBJECTS
CLOBBER.include 'reginaldo'

task :default => 'reginaldo'

file 'reginaldo' => OBJECTS do
	sh "#{CC} -o reginaldo #{OBJECTS} #{LDFLAGS}"
end

rule '.o'        => '.c'    do |t|
	sh "#{CC} #{CFLAGS} -o #{t.name} -c #{t.source}"
end