require 'rake/clean'
require 'rake/extensiontask'
require 'rspec/core/rake_task'

spec    = Gem::Specification.load Dir['*.gemspec'][0]

Rake::ExtensionTask.new 'osimplex', spec do |ext|
  RUBY_VERSION  =~ /(\d+.\d+)/
  ext.lib_dir   = "lib/osimplex/#{$1}"
end

task default:   :spec
task spec:      :compile

RSpec::Core::RakeTask.new do |t|
end
