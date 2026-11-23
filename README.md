# Aventura del Mago - RPG por texto

Proyecto Final de Programacion Orientada a Objetos 2026-2
Pontificia Universidad Javeriana Cali

## Descripcion
Juego de rol por consola en C++. Escoges un mago (fuego, hielo o rayo)
y atraviesas tres habitaciones enfrentando al Kitsune, la Esfinge y la
Hidra de Lerna. Cada enemigo vencido da experiencia para subir de nivel,
y la partida se puede guardar y cargar desde un archivo de texto.

## Como compilar
g++ *.cpp -o juego
./juego

## Conceptos de POO usados
- Abstraccion: clase Entidad abstracta (atacar es virtual pura)
- Herencia: Entidad -> Jugador -> MagoFuego / MagoHielo / MagoRayo y Entidad -> Kitsune / Esfinge / HidraDeLerna
- Polimorfismo: metodos virtuales (atacar, recibirDanio, ataqueFuerte, habilidadEspecial, getRecompensaExp)
- Encapsulamiento: atributos protected/private con getters
- Memoria dinamica: new/delete de enemigos, habitaciones y jugador
- Contenedores: vector de objetos (inventario) y de enemigos
- Persistencia: guardar y cargar partida en partida.txt

## Integrantes
- (nombres)
