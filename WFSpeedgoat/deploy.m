function deploy(rts_ip)

    out = 'hoi!'
    tg = slrealtime(rts_ip)
    tg.connect
    stop(tg)
    tg.load('wturbines')
    
    start(tg)

end