# MUST be run from a shell (e.g. git bash) or on linux

# This file is currently created with a single djinni file in mind
# TODO: May want to make it more extensible later

import subprocess
import os

def cleanPath( path ):
    return path.replace("\\", "/")

## Set the namespace, prefix, etc.

# C++ namespace
cpp_namespace = "engine"

# Objective-C Prefix
objc_prefix = "engine"

# Java Package Name
java_package = "com.example.steve.engine"


## Set the generation directories

script_directory = cleanPath( os.path.dirname(os.path.abspath(__file__)) )

# Set to the root of the engine
generated_dir = script_directory + "/../generated"

# List of djinni files to generate from
djinni_files = [ script_directory + '/../engine/GameInteractor.djinni' ]

cpp_out = generated_dir + "/cpp"
objc_out = generated_dir + "/objc"
jni_out = generated_dir + "/jni"
java_out = generated_dir + "/java"

djinni_exec = "../../dependencies/djinni/src/run"

## Remove the current generated folder for regeneration
# May want to optimize so that regeneration occurs only if the file has changed

#subprocess.call(["rm", "-rf", generated_dir])

## Djinni generation

for djinni_file in djinni_files:
    file_exists = os.path.exists( djinni_file )
    if not file_exists:
        print("Djinni File " + djinni_file + " does not exist!")
        continue
    
    subprocess.call( [  
        "bash", djinni_exec,
        "--java-out", java_out,
        "--java-package", java_package,
        "--ident-java-field", "mFooBar",
        "--cpp-out", cpp_out,
        "--cpp-namespace", cpp_namespace,
        "--jni-out", jni_out,
        "--ident-jni-class", "NativeFooBar",
        "--ident-jni-file", "NativeFooBar",
        "--objc-out", objc_out,
        "--objcpp-out", objc_out,
        "--idl", djinni_file
    ], shell=True)
    