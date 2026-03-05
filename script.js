const notesGrid = document.getElementById('notes-grid');
const addBtn = document.getElementById('add-btn');

// Cargar notas al iniciar
window.addEventListener('DOMContentLoaded', () => {
    const savedNotes = JSON.parse(localStorage.getItem('my-notes')) || [];
    savedNotes.forEach(content => createNoteElement(content));
    lucide.createIcons(); // Inicializa los iconos
});

// Crear una nueva nota al hacer click
addBtn.addEventListener('click', () => {
    createNoteElement();
    saveNotes();
});

function createNoteElement(content = "") {
    const noteDiv = document.createElement('div');
    noteDiv.classList.add('note-card');

    noteDiv.innerHTML = `
        <textarea placeholder="Escribe algo aquí...">${content}</textarea>
        <div class="note-footer">
            <button class="delete-btn"><i data-lucide="trash-2"></i></button>
        </div>
    `;

    const textarea = noteDiv.querySelector('textarea');
    const deleteBtn = noteDiv.querySelector('delete-btn');

    // Guardar mientras se escribe
    textarea.addEventListener('input', saveNotes);

    // Borrar nota
    noteDiv.querySelector('.delete-btn').addEventListener('click', () => {
        noteDiv.remove();
        saveNotes();
    });

    notesGrid.appendChild(noteDiv);
    lucide.createIcons(); // Refresca iconos para la nueva nota
}

function saveNotes() {
    const notes = [];
    document.querySelectorAll('textarea').forEach(textarea => {
        notes.push(textarea.value);
    });
    localStorage.setItem('my-notes', JSON.stringify(notes));
}