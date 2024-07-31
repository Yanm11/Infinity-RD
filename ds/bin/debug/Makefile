gd -fPIC -shared -o libwd.so ../../src/uid.c ../../src/task.c ../../src/heap.c ../../src/hpq.c ../../src/hscheduler.c ../../src/imortal.c ../../src/dvector.c -I ../../include/

gd -o watchdog ../../test/watchdog_test.c -L. -lwd -I ../../include/

gd -o imortal ../../test/imortal_test.c -L. -lwd -I ../../include/

