# iana-tools

以下命令都在项目跟目录下执行

编译

```bash
make
```

下载原始文件

```bash
wget -P ./data/ http://ftp.apnic.net/apnic/stats/apnic/delegated-apnic-latest
```

生成ipset.conf格式的文件

```bash
./bin/iana-tools                                                            \
  -file="./data/delegated-apnic-latest"                                     \
  -cc="CN"                                                                  \
  -type="ipv4"                                                              \
  -headers="create china hash:net family inet hashsize 2048 maxelem 65536"  \
  -prefix="add china " > ./data/ipset.conf
```
