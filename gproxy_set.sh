#!/bin/bash
BASHRC=`readlink -f $HOME/.bashrc`
proxy=""
if [ ! -z "$1" ]; then
    if [ -z "$2" ]; then
        proxy=$1":8080"
    else
        proxy=$1":"$2
    fi
fi
echo $proxy
function set_env_proxy() 
{
    for type in "http" "https"; do
        sed -i "/export ${type}_proxy\=/d" $BASHRC
    done

    if [ "" == "$proxy" ]; then
        return 
    fi
    
    echo "export http_proxy=\"http://${proxy}/\"" >> $BASHRC
    echo "export https_proxy=\"https://${proxy}/\"" >> $BASHRC
}   
function set_apt_proxy(){
    apt="/etc/apt/apt.conf";
    cat /dev/null > $apt
    if [ "$proxy" == "" ]; then
        return 
    fi
    echo "Acquire::http::Proxy \"http://${proxy}\";" >> $apt
    echo "Acquire::https::Proxy \"https://${proxy}\";" >> $apt
}
[ "$3" == "1" ] && set_env_proxy
[ "$4" == "1" ] && set_apt_proxy

echo "Done"