import express from 'express';
import { Server } from 'socket.io';
import http from 'http';

const app = express();
const server = http.createServer(app);
const io = new Server(server);

app.use(express.static('static'));

io.on('connection', (socket) => {
  console.log('new connection');
  let name;

  socket.on('name', (n) => {
    console.log(n);
    name = n;
    socket.broadcast.emit('join', name);
  });

  socket.on('text', (text) => {
    console.log(text);
    socket.broadcast.emit('text', { name, text });
  });
});

server.listen(4000);