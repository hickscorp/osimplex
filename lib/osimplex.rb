require 'osimplex/version'

begin
  RUBY_VERSION  =~ /(\d+.\d+)/
  require "osimplex/#{ $1 }/osimplex.so"
rescue LoadError
  require "osimplex/#{ $1 }/osimplex.bundle"
end

require 'osimplex/generator'
