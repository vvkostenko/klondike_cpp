# Поставим gcc-5
sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test
sudo apt-get update -qq
sudo apt-get install -qq g++-5
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-5 90


# Поддержка кросс-компиляции
#if [ "$TARGET_CPU" == "x86" ]; then
#    sudo dpkg --add-architecture i386
#    sudo apt-get -qq update
#    sudo apt-get install -y g++-5-multilib
#fi