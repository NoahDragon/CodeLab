#!/bin/bash
## Run the script on brand new machine.

PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin
export PATH

apt-get update
apt-get -qq install build-essential

## Install NodeJs
curl -sL https://deb.nodesource.com/setup_7.x | bash -
apt-get -qq install -y nodejs

## Install Vim
apt-get -qq install vim

## Install Docker
apt-get -qq install apt-transport-https ca-certificates
apt-key adv --keyserver hkp://p80.pool.sks-keyservers.net:80 --recv-keys 58118E89F3A912897C070ADBF76221572C52609D
echo "deb https://apt.dockerproject.org/repo ubuntu-trusty main" | sudo tee /etc/apt/sources.list.d/docker.list   # For Ubuntu 14.04
apt-get update
apt-get -qq install docker-engine
service docker start

## Install Git
apt-get -qq install git

