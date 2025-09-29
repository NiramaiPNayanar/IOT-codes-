# httpd-vhosts @ C:\wamp64\bin\apache\apache2.4.54.2\conf\extra\httpd.vhosts
```
# Virtual Hosts
#
<VirtualHost *:80>
  ServerName localhost
  ServerAlias localhost
  DocumentRoot "${INSTALL_DIR}/www"
  <Directory "${INSTALL_DIR}/www/">
    Options +Indexes +Includes +FollowSymLinks +MultiViews
    AllowOverride All
    Require all granted
  </Directory>
</VirtualHost>
```

> windows defender firewall with advanced security -> inbound rules -> port -> 80 -> eval -> finish

> restart WAMP server