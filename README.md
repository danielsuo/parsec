# Princeton Application Repository for Shared-Memory Computers (PARSEC)

## Getting started on Ubuntu 16.04
1. Install Docker
2. ```./bin/install_deps```
3. ```./bin/build dev```
4. ```./bin/run -a run -p blackscholes -i simdev -n 32```

## Building without docker and include shared libraries
1. Clone this repository
- Make any fixes to parsec-3.0 [examples](https://yulistic.gitlab.io/2016/05/parsec-3.0-installation-issues/)
2. Grab parsec-2.1 binaries [link](http://parsec.cs.princeton.edu/download/2.1/binaries/parsec-2.1-amd64-linux.tar.gz)
3. Download [Magic Ermine Pro](http://www.magicermine.com/trial/ErmineProTrial.x86_64/ErmineProTrial.x86_64/ErmineProTrial.x86_64.html)
4. Run the following:

```bash
# Build
pushd parsec-3.0
./bin/parsecmgmt -a build -p parsec
popd

# Copy x264 from parsec-2.1
cp ~/parsec-2.1/pkgs/apps/x264/inst/amd64-linux.gcc-pthreads.pre/bin/x264 ~/parsec-3.0/pkgs/apps/x264/inst/amd64-linux.gcc/bin/x264

# Backup executables
find parsec-3.0/pkgs -type f -perm /a+x | grep amd64 | grep bin/ | grep -v libs/ | grep -v tools/ | xargs -I {} cp "{}" "{}".bak

# Use Ermine to package up shared libraries
find parsec-3.0/pkgs -type f -perm /a+x | grep amd64 | grep bin/ | grep -v libs/ | grep -v tools/ | grep -v bak | xargs -I {} ~/ErmineProTrial.x86_64 "{}".bak --output "{}"

# Clean up (keep backups)
# find parsec-3.0/pkgs -type f -perm /a+x | grep amd64 | grep bin/ | grep -v libs/ | grep -v tools/ | grep -v bak | xargs rm

# Move relevant files
mkdir -p parsec-3.0-stripped

# Copy binaries
find parsec-3.0/pkgs -type f -perm /a+x | grep amd64 | grep bin/ | grep -v libs/ | grep -v tools/ | xargs -I {} cp --parents "{}" parsec-3.0-stripped

# Copy data
find parsec-3.0/pkgs | grep "input.*tar" | xargs -I {} cp --parents "{}" parsec-3.0-stripped

# Copy configs
find parsec-3.0 | grep runconf | grep -v config/ | grep -v man/ | grep -v ext/ | xargs -I {} cp --parent "{}" parsec-3.0-stripped

# Copy global configs
cp -R parsec-3.0/config parsec-3.0-stripped

# Copy scripts
cp -R parsec-3.0/bin parsec-3.0-stripped

# Clean up
mv parsec-3.0-stripped/parsec-3.0/* parsec-3.0-stripped
rm -rf parsec-3.0-stripped/parsec-3.0

# Package
tar czvf parsec-3.0-stripped.tar.gz parsec-3.0-stripped/
```
