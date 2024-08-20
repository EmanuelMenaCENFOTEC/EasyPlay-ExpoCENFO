function capturarDatos() {
    // captura los valores de los inputs
    const inputsAccion = document.getElementsByClassName('input-box');
    let hexString = '';

    for (const input of inputsAccion) {
        let texto = input.value;

        for (let i = 0; i < texto.length; i++) {
            let hexValue = texto.charCodeAt(i).toString(16).toUpperCase();
            hexString += hexValue + 'x9D';
        }
    }

    if (hexString.endsWith('x9D')) {
        hexString = hexString.slice(0, -3);
    }

    console.log(hexString);

    blehKeyboard.print(hexString);
    // o
    blehMouse.print(hexString);
}

document.addEventListener('DOMContentLoaded', function() {
    console.log('DOM fully loaded and parsed');
    const botonRFID = document.getElementById('botonRFID');
    if (botonRFID) {
        botonRFID.addEventListener('click', capturarDatos);
    } else {
        console.error('El botón RFID no se encontró.');
    }
});