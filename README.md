# Branch para los slaves

Pensé en hacer un branch solo para los slaves y otro para el master. Creo que va a ser más sencillo programar y ver donde está el error. Sino es jugar con muchas variables a la vez y no tengo ganas de renegar con eso. 

Está hecho para que el ESP reciba los datos del MASTER (ESP1) y haga lo que les mostré en el depto de rodri. Lee el puerto del IR y apaga las tiras. 

Juego con un flag para permitir cuando recibe. 

Cuando interactuo con el IR, el ESP slave manda un bool de *recibido* al MASTER para que envie el siguiente dato. 

Funcionan de manera independiente asi que el *peer* hace solo con el master. 
