require File.expand_path('../lib/osimplex/version', __FILE__)

# somewhere in your Rakefile, define your gem spec
Gem::Specification.new do |s|
  s.name              = 'osimplex'
  s.version           = OSimplex::VERSION
  s.date              = Time.now.strftime '%Y-%m-%d'
  s.authors           = [ 'HERAULT-MARTIN Pierre' ]
  s.summary           = 'OpenSimplex Ruby C Extension'
  s.description       = ''
  s.email             = [ 'HicksCorp@GMail.com' ]
  s.homepage          = 'https://github.com/hickscorp/osimplex'
  s.licenses          = [ 'MIT' ]

  s.files             = Dir.glob [
                          'Rakefile',
                          'lib/**/*.{rb,yml}',
                          'lib',
                          'ext/**/*.{c,h,rb}',
                          'spec/**/*.*'
                        ]

  s.extensions        << 'ext/osimplex/extconf.rb'
  s.rubyforge_project = 'osimplex'
  s.test_files        = Dir[ 'spec/**/*.*' ]

  s.add_development_dependency 'rake-compiler', '~> 0.8.1'
  s.add_development_dependency 'rspec', '~> 2.10.0'

end
