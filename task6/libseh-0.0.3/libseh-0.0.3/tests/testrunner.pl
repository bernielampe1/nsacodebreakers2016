#!/usr/bin/perl

if(-f "tests.log") { unlink("tests.log"); }

my @tests = qw/div_zero finally null_pointer noexcept null_pointer_cxx/;

for my $g (@tests) {
    print "Running test $g...";
    if(system("$g >> tests.log") != 0) {
        print STDERR "ERROR: test $g failed!!!\n";
        exit 1;
    }
    else {
        print "success!\n";
    }
}

print "SUCCESS: All tests passed!\n";
