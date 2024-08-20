console.log("hola");

function capturarDatos() {
    // capturar los valores de los inputs
    const inputsAccion = document.getElementsByClassName('input-box');
    // recorrer los inputs e imprimirlos
    for (const input of inputsAccion) {
        console.log(input.value);
    }
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