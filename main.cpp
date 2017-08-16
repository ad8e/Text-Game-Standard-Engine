#include "htmloutput.h"

void main_menu_later();
void engine_choice();
void emscripten_notes() {
	o(R"(Interactive Text is just a wrapper around an output function. Emscripten does the real work converting C++ to HTML. Emscripten has some catches.
For filesystem read/write, you have to add some emscripten sync functions if you want saves, and you need --preload-file if you want to load pre-existing files. Alternatively, you can use html's localStorage for saves.
Keyboard input handling is through Javascript, using onkeypress, which only supports keys with concrete glyphs, like "a" and "=". To support keys like "Ctrl" and arrow keys, you'll need onkeydown, number-to-symbol tables for each browser, and browser sniffing.
When testing in Chrome and IE, if you're running the html file on your computer instead of a server, you'll need to follow emscripten's <a href="https://kripken.github.io/emscripten-site/docs/getting_started/Tutorial.html#using-files">guide on setting up a localhost web server for development</a>. Firefox doesn't need this step.
If your console output messages aren't showing, add '\n' to the end of each line. Use printf instead of iostreams, because cout has a <a href="https://floooh.github.io/2016/08/27/asmjs-diet.html">large fixed cost</a>, 250KB.
)");
	o("Return", engine_choice, n)(r);
}

void other_engines() {
	o(R"(Java has severe UI and performance problems in every text game I've seen.
Ren'Py is powerful, mature, and well-supported; it is good if you want to build a Visual Novel.
IF parser engines, like Inform, place restrictions on your format and require a language you will never use anywhere else. They're decent within their format, but most players will refuse to play them.
RAGS, QSP, and Quest are dumpster fires.
Adobe Flash is dead.
Unity has some formatting, and it can produce HTML files, but for a text game, it's too heavy and proprietary. Starting up takes significant work, with no benefit.
HTML is best for a text game. It has colors, fonts, sectioned displays, buttons, and pictures. Its wide developer support makes it supreme in performance and flexibility. It is multiplatform. Most importantly, people play browser games, but most people won't play downloaded games.
For any minor engine, be aware that if its developer vanishes, your work could become useless. Even if the engine is open-source, it's unlikely anyone else will step in. Interactive Text faces this same issue, and tries to be small so that it's easy to modify. However, you should still be mindful.
)");
	o("Return", engine_choice, n)(r);
}

void engine_choice() {
	o(R"(<h4>How do I build a text game?</h4>
<a href="https://twinery.org/">Twine</a> is a strong choice. You can write without programming knowledge. It has built-in saves. It allows undo in-game. Its editor is annoying and laggy, but tolerable. However, Twine games lasting 10 hours freeze for several seconds after every click, and restarting the browser doesn't help. This makes long Twine games unplayable.
Interactive Text is an alternative for those who know C++. You should use it if you require complex mechanics and don't want to write Javascript. It doesn't have built-in saves.
Both options create HTML files that can be run in a browser.
)");
	o("Other engines", other_engines)('\n');
	o("Notes on emscripten", emscripten_notes)('\n');
	o("Return to the main menu", main_menu_later, n)(r);
}

int incrementor = 0;
void guestbook_incrementor() {
	o("You doodle on the board.");
	++incrementor;
	main_menu_later();
}
void erase_incrementor() {
	o("You wipe the board clean.\n");
	incrementor = 0;
	main_menu_later();
}

void main_menu_later() {
	if (incrementor != 0) {
		o("Draw on it again?", guestbook_incrementor)("Or")("erase the board?", erase_incrementor);
		o(R"(<div style="text-align:center;">)");
		for (int start = incrementor; start; --start) o(R"(<img src="Fractal_fern_explained.png" alt="doodle" style="width:333px; height:465px">)");
		o("</div>");
	}
	o(R"(
<a href="https://github.com/ad8e/Interactive-Text">Interactive Text</a> turns C++ text games into HTML. Features:
<ul>
<li>simple: o() to output</li>
<li>scrollback history</li>
<li>keyboard shortcuts for links</li>
<li>Public Domain: free, no conditions</li>
</ul>
Technical details:
<ul>
<li>lightweight and performant: this entire webpage is 65KB to download</li>
<li>typography scales across large and small screens, adjusting line spacing and margin</li>
<li>link format avoids empty history entries and empty new tabs on middle click</li>
<li>transparent support for screenreaders</li>
<li>tested in IE, Firefox, and Chrome</li>
<li>HTML customization is easy</li>
</ul>
<a href="https://github.com/ad8e/Interactive-Text">Download the engine.</a>
)");

	o("Advice on engine choice", engine_choice)('\n');

	if (incrementor == 0) o("In front of you is a board.")("Draw on it?", guestbook_incrementor);
	o(r);
}

int main() {
	main_menu_later();
}