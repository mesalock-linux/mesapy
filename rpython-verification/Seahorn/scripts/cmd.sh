find /media/qian/dataset/pypy/rpython/translator/ -type f -name "*.c" -exec basename {} \; > /tmp/usession-default-2/testing_1/rpython_c.namelist
find /tmp/usession-default-2/testing_1/ -type f -name "*.c" -exec basename {} \; > /tmp/usession-default-2/testing_1/exe.namelist
cat /tmp/usession-default-2/testing_1/exe.namelist | cut -f 1 -d '.' > /tmp/usession-default-2/testing_1/exe.name
cat /tmp/usession-default-2/testing_1/rpython_c.namelist | cut -f 1 -d '.' > /tmp/usession-default-2/testing_1/rpython.name
sort /tmp/usession-default-2/testing_1/rpython.name  /tmp/usession-default-2/testing_1/exe.name | uniq -d |xargs -I % echo %.o > /tmp/usession-default-2/testing_1/comm.namelist
cat /tmp/usession-default-2/testing_1/comm.namelist | xargs -I % extract-bc % --output /tmp/usession-default-2/testing_1/bc/%.bc
ls /tmp/usession-default-2/testing_1/bc/*|xargs -I % ./sh.sh % > /tmp/usession-default-2/testing_1/results
paste -d " " /tmp/usession-default-2/testing_1/comm.namelist /tmp/usession-default-2/testing_1/results > /tmp/usession-default-2/testing_1/seahorn.results
