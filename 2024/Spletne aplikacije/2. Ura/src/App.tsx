import { useState } from "react";
import {
	BrowserRouter as Router,
	Route,
	NavLink,
	Routes,
} from "react-router-dom";
import Home from "./components/home";
import About from "./components/about";
import Contact from "./components/contact";
import "./App.css";

function App() {
	return (
		<div>
			<Router>
				<nav>
					<NavLink to="/home">Home</NavLink>
					<NavLink to="/about">About</NavLink>
					<NavLink to="/contact">Contact</NavLink>
				</nav>
				<div className="routes">
					<Routes>
						<Route path="/home" element={<Home />} />
						<Route path="/about" element={<About />} />
						<Route path="/contact" element={<Contact />} />
					</Routes>
				</div>
			</Router>
		</div>
	);
}

export default App;
