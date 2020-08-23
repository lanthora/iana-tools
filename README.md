# iana-tools

```bash
wget http://ftp.apnic.net/apnic/stats/apnic/delegated-apnic-latest
```

```bash
./iana-tools -file="../data/delegated-apnic-latest"                         \
  -cc="CN"                                                                  \
  -type="ipv4"                                                              \
  -headers="create china hash:net family inet hashsize 2048 maxelem 65536"  \
  -prefix="add china " > ../data/ipset.conf
```