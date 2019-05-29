#!/usr/bin/env bash
# Djinni file location
djinni_file="../engine/GameInteractor.djinni"
# c++ namespace
namespace="engine"
# Objective-C prefix
objc_prefix="engine"
# Java package
java_package="com.example.steve.engine"
### Script
# get java directory
# java_dir=$(echo $java_package | tr . /)
# directories for the generated src files
cpp_out="../generated/cpp"
objc_out="../generated/objc"
jni_out="../generated/jni"
java_out="../generated/java"
# remove everything from these directories
rm -rf $cpp_out
rm -rf $jni_out
rm -rf $objc_out
rm -rf $java_out
# Create our files (using the djinni submodule)
../../dependencies/djinni/src/run \
    --java-out $java_out \
    --java-package $java_package \
    --ident-java-field mFooBar \
    --cpp-out $cpp_out \
    --cpp-namespace $namespace \
    --jni-out $jni_out \
    --ident-jni-class NativeFooBar \
    --ident-jni-file NativeFooBar \
    --objc-out $objc_out \
    --objc-type-prefix $objc_prefix \
    --objcpp-out $objc_out \
    --idl $djinni_file