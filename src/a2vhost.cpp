#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
using namespace std;

/**            
 * a2vhost - virtualhost generator for windows
 * Just-for-fun projects by Hein Thanth
 * Depends on sudo, apache24
 */

void showHelp();
string _apache_root = "C:/Apache24/";

class VirtualHost {
    public:
        VirtualHost(string domain, string root, bool ssl) {
            this->domain = domain;
            this->root = root;
            this->ssl = ssl;
        }
        void create() {
            ofstream vhostfile;
            ofstream vhostsslfile;
            vhostfile.open(_apache_root + "conf/extra/vhosts/" + this->domain + ".conf");
            if( vhostfile.is_open() ) {
                vhostfile << 
                "<VirtualHost *:80>\n"
                "\tServerName " + this->domain + "\n"
                "\tServerAlias " + this->domain + ".*.xip.io\n"
                "\tServerAdmin admin@" + this->domain + "\n"
                "\tDocumentRoot \"" + this->root + "\"\n"
                "\t<Directory \"" + this->root + "\">\n"
                "\t\tOptions +Indexes +FollowSymLinks +ExecCGI\n"
                "\t\tAllowOverride All\n"
                "\t\tRequire all granted\n"
                "\t</Directory>\n"
                "\tErrorLog \"logs/" + this->domain + "-error.log\"\n"
                "\tCustomLog \"logs/" + this->domain + "-access.log\" common\n"
                "</VirtualHost>";
                vhostfile.close();
            } else {
                cout << "\nSomething went wrong :')\n\n";
                exit(0);
            }
            if(this->ssl) {
                string gensslcommand = "openssl req -x509 -nodes -days 365 -newkey rsa:2048 -keyout " + _apache_root + "conf/extra/ssl/" + this->domain + ".key -out " + _apache_root + "conf/extra/ssl/" + this->domain + ".crt";
                system(gensslcommand.c_str());
                vhostsslfile.open(_apache_root + "conf/extra/vhosts/" + this->domain + "-ssl.conf");
                if( vhostsslfile.is_open() ) {
                    vhostsslfile << 
                    "<VirtualHost *:443>\n"
                    "\tServerName " + this->domain + "\n"
                    "\tServerAlias " + this->domain + ".*.xip.io\n"
                    "\tServerAdmin admin@" + this->domain + "\n"
                    "\tDocumentRoot \"" + this->root + "\"\n"
                    "\t<Directory \"" + this->root + "\">\n"
                    "\t\tOptions +Indexes +FollowSymLinks +ExecCGI\n"
                    "\t\tAllowOverride All\n"
                    "\t\tRequire all granted\n"
                    "\t</Directory>\n"
                    "\tSSLEngine On\n"
                    "\tSSLCertificateFile \"${SRVROOT}/conf/extra/ssl/" + this->domain + ".crt\"\n"
                    "\tSSLCertificateKeyFile \"${SRVROOT}/conf/extra/ssl/" + this->domain + ".key\"\n"
                    "\tErrorLog \"logs/" + this->domain + "-error.log\"\n"
                    "\tCustomLog \"logs/" + this->domain + "-access.log\" common\n"
                    "</VirtualHost>";
                    vhostsslfile.close();
                } else {
                    cout << "\nSomething went wrong :')\n\n";
                    exit(0);
                }
            }
        }  
        void writeHost() {
            system("copy C:\\windows\\system32\\drivers\\etc\\hosts C:\\windows\\system32\\drivers\\etc\\hosts.bak 1>nul");
            ofstream hosts("C:/windows/system32/drivers/etc/hosts", ios::app);
            if(hosts.is_open()) {
                hosts << "127.0.0.1\t" + this->domain + "\n";
                hosts.close();
            } else {
                cout << "\nSomething went wrong :') \n\n";
                exit(0);
            }
            system("httpd -k restart");
        }
        void inform() {
            cout << "Generated successfully!" << endl;
            cout << "Configuration files are stored at " + _apache_root + "conf/extra/vhosts/" << endl;
            if(this->ssl) {
                cout << "SSL Certificate files are stored at" + _apache_root + "conf/extra/ssl/" << endl;
            }
        }
    private:
        string domain;
        string root;
        bool ssl;
};

int main(int argc, char* argv[]) {
    if( argc < 2 || argc > 7 || ( argc == 2 && (string(argv[1]) == "--help" || string(argv[1]) == "-h") ) ) {
        showHelp();
    }
    string _tmp_domain = "", _tmp_root = "";
    bool _tmp_ssl;

    for(int i = 1; i < argc; i++) {
        if( string(argv[i]) == "--domain" ) {
            _tmp_domain = argv[i + 1];
            i++;
        } else if( string(argv[i]) == "--root" ) {
            _tmp_root = argv[i + 1];
            i++;
        } else if( string(argv[i]) == "--ssl" ) {
            if( string(argv[i + 1]) == "true" ) {
                _tmp_ssl = true;
            } else {
                _tmp_ssl = false;
            }
            i++;
        }
    }
    VirtualHost vhost(_tmp_domain, _tmp_root, _tmp_ssl);
    vhost.create();
    vhost.writeHost();
    vhost.inform();
    return 0;
}

void showHelp() {
    cout << 
    "      ___     _           _   \n"
    " __ _|_  )_ _| |_  ___ __| |_ \n"
    "/ _` |/ /\\ V / ' \\/ _ (_-<  _|\n"
    "\\__,_/___|\\_/|_||_\\___/__/\\__|\n" << endl;
    cout << "VirtualHost Generator for Apache2" << endl;
    cout << "a2vhost 1.0.2 - (c) Hein Thanth" << endl;
    cout << "https://github.com/heinthanth/a2vhost-windows" << endl;
    cout << "\nUsage: a2vhost [option] [value]\n\n";
    cout << "  --domain\tDomain for VirtualHost\n";
    cout << "\t\t*\tDomain name of the virtual host\n\n";
    cout << "  --root\tDocument Root of VirtualHost\n";
    cout << "\t\t*\tAbsolute path of document root of virtual host\n\n";
    cout << "  --ssl\t\tInclude SSL VirtualHost\n";
    cout << "\t\t*\twhether virtualhost with ssl should generate [true/false]\n\n";
    exit(0);
}