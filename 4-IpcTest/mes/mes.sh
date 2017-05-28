gcc MesRx.c -o mesrx
gcc MesTx.c -o mestx

su -c "./mestx & ./mesrx"
