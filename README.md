# OpenSimplex Ruby Gem

## What is it?

The only [OpenSimplex implementation I could find in C](https://github.com/smcameron/open-simplex-noise-in-c) was adapted by @smcameron.

This gem is a mere attempt at exposing his work to the ruby community.

As there is no test coverage yet, use it at your own risk.

## Get started

After cloning the repository, you can test that the extension was properly compiled:

```
git clone ...
bundle
rake compile
bundle exec irb -Ilib:ext -r osimplex
```

Then, from the IRB shell:

```
OSimplex::Generator.new(123).get_3d 42, 42, 42
 => 0.17865485575013934
```

You could also directly reference the gem from your Gemfile:

```
gem 'osimplex'
```
