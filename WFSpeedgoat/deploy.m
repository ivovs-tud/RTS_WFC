tg = slrealtime('172.19.3.43');
tg.connect;

tg.load('wturbines');

tg.setparam('localIP', '172.19.3.43');
tg.setparam('pcIP', '172.19.3.214');
tg.setparam('plcIP', '172.19.3.190');