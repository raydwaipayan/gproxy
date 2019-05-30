#!/bin/bash
#proxy=$(./gproxy_main)
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
[ "$3" == "1" ] && set_env_proxy
echo "Done"