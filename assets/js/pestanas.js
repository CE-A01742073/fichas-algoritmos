// Convierte cada bloque .codigo en pestañas: Pseudocódigo, C++ y Python.
document.querySelectorAll('.codigo').forEach(function (caja) {
  var paneles = caja.querySelectorAll('.pestana');
  if (paneles.length < 2) return;
  var barra = document.createElement('div');
  barra.className = 'pestanas';
  barra.setAttribute('role', 'tablist');
  paneles.forEach(function (panel, i) {
    var boton = document.createElement('button');
    boton.type = 'button';
    boton.textContent = panel.getAttribute('data-nombre');
    boton.setAttribute('role', 'tab');
    boton.addEventListener('click', function () {
      paneles.forEach(function (p) { p.hidden = true; });
      barra.querySelectorAll('button').forEach(function (b) { b.setAttribute('aria-selected', 'false'); });
      panel.hidden = false;
      boton.setAttribute('aria-selected', 'true');
    });
    barra.appendChild(boton);
    panel.hidden = i !== 0;
    boton.setAttribute('aria-selected', i === 0 ? 'true' : 'false');
  });
  caja.classList.add('con-pestanas');
  caja.insertBefore(barra, caja.firstChild);
});
