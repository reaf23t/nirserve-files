#!/usr/bin/env pybricks-micropython

from pybricks.hubs import EV3Brick
from pybricks.ev3devices import Motor
from pybricks.parameters import Port, Direction
from pybricks.tools import wait

# Inicializa o EV3
ev3 = EV3Brick()

# Configura os motores (definir motores B e C)
motor_esquerdo = Motor(Port.B)
motor_direito = Motor(Port.C)

# Quando o programa iniciar
ev3.speaker.beep()  # Sinal de início

# Repete para sempre
while True:
    # Mover para trás por 3 rotações
    motor_esquerdo.run_angle(-200, 3 * 360)  # -200 = velocidade negativa (trás)
    motor_direito.run_angle(-200, 3 * 360)
    
    # Pequena pausa entre os movimentos
    wait(500)
    
    # Mover por 2.70 rotações com velocidades diferentes (70% e -70%)
    # 70% de velocidade máxima (cerca de 700 RPM) = 490 RPM
    motor_esquerdo.run_angle(490, 2.70 * 360)    # 70% para frente
    motor_direito.run_angle(-490, 2.70 * 360)    # -70% para trás (faz curva)
    
    wait(500)  # Pequena pausa antes de repetir