const input = document.getElementById('input');
const button = document.getElementById('send');
const chat = document.getElementById('chat');

const name = prompt('Enter your name');

const socket = io();

socket.on('connect', () => {
  console.log('connected');

  socket.emit('name', name);
});

socket.on('text', (text) => {
  console.log(text);
  addText(text.name, text.text, false);
});

socket.on('join', (name) => {
  console.log(`${name} has joined the chat.`);
  joinedChat(name);
});

button.addEventListener('click', () => {
  socket.emit('text', input.value);
  addText(name, input.value, true);
  input.value = '';
});

function addText(name, text, mine) {
  const bubble = document.createElement('div');
  const p = document.createElement('p');
  p.innerHTML = `<b>${name}:</b> ${text}`;

  bubble.classList.add('message-bubble');

  if (mine) {
    bubble.classList.add('my-message');
  }

  bubble.appendChild(p);
  chat.appendChild(bubble);
}

function joinedChat(name) {
  const p = document.createElement('p');
  p.innerText = `${name} has joined the chat`;
  p.style.fontWeight = 'bold';
  p.style.color = 'white';
  chat.appendChild(p);
}
