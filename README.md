# GPROXY
Gproxy is a simple C gtk based application and uses a shell script underneath. It simplifies the process of setting proxy for various system utilities in *nix.

## Requirements
* gcc
* gtk+-3.0

## Usage
```
chmod +x install.sh
sudo ./install.sh
```

## How it works
### Workflow
- The GTK based application captures the user input and sends corresponding data to a shell script.
- The shell program checks for the options and activates the required proxy settings.

### Appearance
![](assets/view.png?raw=true)