require 'mkmf'

extension_name  = 'osimplex'
dir_config      extension_name

$CFLAGS         += ' -DRUBY_19' if RUBY_VERSION =~ /^1.9/
$CFLAGS         += " -std=gnu99"
$warnflags.gsub!('-Wdeclaration-after-statement', '') if $warnflags

create_makefile extension_name
