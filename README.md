# Branch para los slaves

Pensé en hacer un branch solo para los slaves y otro para el master. Creo que va a ser más sencillo programar y ver donde está el error. Sino es jugar con muchas variables a la vez y no tengo ganas de renegar con eso. 

Está hecho para que el ESP reciba los datos del MASTER (ESP1) y haga lo que les mostré en el depto de rodri. Lee el puerto del IR y apaga las tiras. 

Juego con un flag para permitir cuando recibe. 

Cuando interactuo con el IR, el ESP slave manda un bool de *recibido* al MASTER para que envie el siguiente dato. 

Funcionan de manera independiente asi que el *peer* hace solo con el master. 


Para hacer las id que son unicas: 

ESP1 MASTER - 0C:B8:15:CB:EE:00

ESP2 SLAVE  - 0C:B8:15:CB:FF:84 id=1

ESP3 SLAVE - 0C:B8:15:CB:FA:1C  id=2
