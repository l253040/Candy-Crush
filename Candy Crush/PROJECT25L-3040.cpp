//
//#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
//#include <iostream>
//#include <cstdlib>   // rand, srand
//#include <fstream>   // save/load
//#include <cmath>     // abs
//using namespace std;
//using namespace sf;
//const int max_row = 10;
//const int max_col = 10;
//int targetgoal = 0;
//int cellSize = 83;
//int score = 0;
//int remainingmoves = 20;
//bool gameOver = false;
//
//Font gameFont;
//SoundBuffer swapBuffer;
//Sound swapSound;
//SoundBuffer gameOverBuffer;
//Sound gameOverSound;
//SoundBuffer failed;
//Sound failedsound;
//SoundBuffer juicy;
//Sound juicysound;
//
//
//
//Font font;
//RectangleShape startBtn(Vector2f(260, 70));
//RectangleShape exitBtn(Vector2f(260, 70));
//RectangleShape howIcon(Vector2f(260, 70));
//RectangleShape loadBtn(Vector2f(260, 70));
//
//Text titleText;
//Text startText;
//Text exitText;
//Text howText;
//Text loadText;
//void updateScore(int matchCount) {
//    if (matchCount == 3)
//        score = score + 10;
//    else if (matchCount == 4)
//        score = score + 20;
//    else if (matchCount >= 5)
//        score = score + 30;
//}
//bool shouldEndGame() {
//    return (score >= targetgoal || remainingmoves <= 0);
//}
//void setTarget(int rows, int cols) {
//    if (rows == 6 && cols == 6)
//        targetgoal = 700;
//    else if (rows == 8 && cols == 8)
//        targetgoal = 1000;
//    else if (rows == 10 && cols == 10)
//        targetgoal = 1200;
//    else
//        targetgoal = 700;
//}
//bool isAdjacent(int row1, int col1, int row2, int col2) {
//    int rowDiff = abs(row1 - row2);
//    int colDiff = abs(col1 - col2);
//    return (rowDiff == 0 && colDiff == 1) || (rowDiff == 1 && colDiff == 0);
//}
//void save(int grid[][max_col], int rows, int cols) {
//    ofstream file("save.txt");
//    if (!file) return;
//
//    file << rows << " " << cols << endl;
//    file << score << " " << remainingmoves << endl;
//    for (int r = 0; r < rows; r++) {
//        for (int c = 0; c < cols; c++) {
//            file << grid[r][c] << " ";
//        }
//        file << "\n";
//    }
//    file.close();
//}
//
//bool load(int grid[][10], int& rows, int& cols) {
//    ifstream file("save.txt");
//    if (!file) return false;
//
//    file >> rows >> cols;
//    file >> score >> remainingmoves;
//
//    for (int r = 0; r < rows; r++)
//        for (int c = 0; c < cols; c++)
//            file >> grid[r][c];
//
//    file.close();
//    return true;
//}
//bool loadingsounds() {
//    bool check = true;
//    if (!swapBuffer.loadFromFile("swap.mp3")) {
//        cout << "swap.mp3 missing!\n";
//        check = false;
//    }
//    swapSound.setBuffer(swapBuffer);
//
//    if (!gameOverBuffer.loadFromFile("gameover.mp3")) {
//        cout << "gameover.mp3 missing!\n";
//        check = false;
//    }
//    gameOverSound.setBuffer(gameOverBuffer);
//
//    if (!failed.loadFromFile("failed.mp3")) {
//        cout << "failed.mp3 missing!\n";
//        check = false;
//    }
//    failedsound.setBuffer(failed);
//
//    if (!juicy.loadFromFile("juicy.mp3")) {
//        cout << "juicy.mp3 missing!\n";
//        check = false;
//    }
//    juicysound.setBuffer(juicy);
//
//    return check;
//}
//
//bool initialmatches(int grid[][max_col], int rows, int cols)
//{
//    // horizontal
//    for (int i = 0; i < rows; i++)
//        for (int j = 0; j < cols - 2; j++)
//            if (grid[i][j] == grid[i][j + 1] && grid[i][j] == grid[i][j + 2])
//                return true;
//
//    // vertical
//    for (int j = 0; j < cols; j++)
//        for (int i = 0; i < rows - 2; i++)
//            if (grid[i][j] == grid[i + 1][j] && grid[i][j] == grid[i + 2][j])
//                return true;
//
//    // diagonal down-right "\" 
//    for (int i = 0; i < rows - 2; i++)
//        for (int j = 0; j < cols - 2; j++)
//            if (grid[i][j] == grid[i + 1][j + 1] && grid[i][j] == grid[i + 2][j + 2])
//                return true;
//
//    // diagonal down-left "/" 
//    for (int i = 0; i < rows - 2; i++)
//        for (int j = 2; j < cols; j++)
//            if (grid[i][j] == grid[i + 1][j - 1] && grid[i][j] == grid[i + 2][j - 2])
//                return true;
//
//    return false;
//}
//
//void InitialBoard(int grid[][max_col], int rows, int cols)
//{
//    do
//    {
//        for (int r = 0; r < rows; r++)
//            for (int c = 0; c < cols; c++)
//                grid[r][c] = rand() % 6;
//    } while (initialmatches(grid, rows, cols));
//}
//
//enum EndResult { END_NONE, END_RESTART, END_MENU };
//EndResult showEndWindow(bool win, int finalScore)
//{
//    RenderWindow resultscreen(VideoMode(500, 350), "Game Result");
//    Font f;
//    if (!f.loadFromFile("arial.ttf"))
//        cout << "FONT ERROR!\n";
//    Text message, scoreText, restartText, menuText;
//    message.setFont(f);
//    scoreText.setFont(f);
//    restartText.setFont(f);
//    menuText.setFont(f);
//
//    message.setCharacterSize(50);
//    message.setFillColor(Color::White);
//    if (win) {
//        message.setString("YOU WIN!");
//        gameOverSound.play();
//    }
//    else {
//        message.setString("YOU LOSE!");
//        failedsound.play();
//    }
//    message.setPosition(120, 30);
//
//
//    string scoreString = "Score: " + to_string(finalScore);
//
//
//    scoreText.setString(scoreString);
//
//
//    scoreText.setCharacterSize(35);
//    scoreText.setFillColor(Color::White);
//    scoreText.setPosition(170, 100);
//
//    RectangleShape restartButton(Vector2f(200, 50));
//    restartButton.setPosition(150, 160);
//    restartButton.setFillColor(Color(180, 200, 220));
//
//    restartText.setString("Restart Game");
//    restartText.setCharacterSize(25);
//    restartText.setFillColor(Color(50, 50, 70));
//    restartText.setPosition(170, 170);
//
//    RectangleShape menubutton(Vector2f(200, 50));
//    menubutton.setPosition(150, 230);
//    menubutton.setFillColor(Color(240, 210, 180));
//
//    menuText.setString("Main Menu");
//    menuText.setCharacterSize(25);
//    menuText.setFillColor(Color(50, 50, 70));
//    menuText.setPosition(190, 240);
//
//    RectangleShape background(Vector2f(500, 350));
//    if (win) {
//        background.setFillColor(Color(100, 160, 120));
//
//    }
//    else
//    {
//        background.setFillColor(Color(170, 100, 100));
//
//    }
//
//
//    while (resultscreen.isOpen())
//    {
//        Event ev;
//        while (resultscreen.pollEvent(ev))
//        {
//            if (ev.type == Event::Closed)
//            {
//                resultscreen.close();
//
//            }
//            if (ev.type == Event::MouseButtonPressed && ev.mouseButton.button == Mouse::Left)
//            {
//                Vector2i m(ev.mouseButton.x, ev.mouseButton.y);
//                if (restartButton.getGlobalBounds().contains((float)m.x, (float)m.y))
//                {
//                    resultscreen.close();
//                    return END_RESTART;
//                }
//                if (menubutton.getGlobalBounds().contains((float)m.x, (float)m.y))
//                {
//                    resultscreen.close();
//                    return END_MENU;
//                }
//            }
//        }
//        resultscreen.clear();
//        resultscreen.draw(background);
//        resultscreen.draw(message);
//        resultscreen.draw(scoreText);
//        resultscreen.draw(restartButton);
//        resultscreen.draw(restartText);
//        resultscreen.draw(menubutton);
//        resultscreen.draw(menuText);
//        resultscreen.display();
//    }
//    return END_MENU;
//}
//
//bool scanMatches(int grid[][max_col], bool removeCell[][max_col], int placeSpecial[][max_col], int rows, int cols)
//{
//    bool found = false;
//
//    // reset remove flags and special markers
//    for (int r = 0; r < rows; r++)
//        for (int c = 0; c < cols; c++)
//        {
//            removeCell[r][c] = false;
//            placeSpecial[r][c] = -1;
//        }
//
//    // HORIZONTAL
//    for (int r = 0; r < rows; r++)
//    {
//        for (int c = 0; c < cols - 2; c++)
//        {
//            int val = grid[r][c];
//            if (val == -1)
//                continue;
//
//            if (grid[r][c + 1] == val && grid[r][c + 2] == val)
//            {
//                found = true;
//                int length = c;
//                int countMatch = 0;
//                while (length < cols && grid[r][length] == val)
//                {
//                    removeCell[r][length] = true;
//                    length++;
//                    countMatch++;
//                }
//
//
//                if (countMatch == 4)
//                {
//
//                    placeSpecial[r][c] = 6;
//                    removeCell[r][c] = false; // is lye k ham na grid[r][c] ki jaga new candy lani ha remove ni krna 
//                }
//                else if (countMatch >= 5)
//                {
//
//                    placeSpecial[r][c] = 7;
//                    removeCell[r][c] = false; // same as above
//                }
//
//                updateScore(countMatch);
//
//            }
//        }
//    }
//
//    // VERTICAL
//    for (int c = 0; c < cols; c++)
//    {
//        for (int r = 0; r < rows - 2; r++)
//        {
//            int val = grid[r][c];
//            if (val == -1)
//                continue;
//
//            if (grid[r + 1][c] == val && grid[r + 2][c] == val)
//            {
//                found = true;
//                int length = r;
//                int countMatch = 0;
//                while (length < rows && grid[length][c] == val)
//                {
//                    removeCell[length][c] = true;
//                    length++;
//                    countMatch++;
//                }
//
//                if (countMatch == 4)
//                {
//                    placeSpecial[r][c] = 6;
//                    removeCell[r][c] = false;
//                }
//                else if (countMatch >= 5)
//                {
//                    placeSpecial[r][c] = 7;
//                    removeCell[r][c] = false;
//                }
//
//                updateScore(countMatch);
//
//            }
//        }
//    }
//
//    // DIAGONAl right
//    for (int i = 0; i < rows - 2; i++)
//    {
//        for (int j = 0; j < cols - 2; j++)
//        {
//            int val = grid[i][j];
//            if (val == -1)
//                continue;
//
//            if (grid[i + 1][j + 1] == val && grid[i + 2][j + 2] == val)
//            {
//                found = true;
//                int rr = i;
//                int cc = j;
//                int countMatch = 0;
//                while (rr < rows && cc < cols && grid[rr][cc] == val)
//                {
//                    removeCell[rr][cc] = true;
//                    rr++; cc++; countMatch++;
//                }
//                if (countMatch == 4)
//                {
//                    placeSpecial[i][j] = 6;
//                    removeCell[i][j] = false;
//                }
//                else if (countMatch >= 5)
//                {
//                    placeSpecial[i][j] = 7;
//                    removeCell[i][j] = false;
//                }
//                updateScore(countMatch);
//
//            }
//        }
//    }
//
//    // DIAGONAL DOWN-LEFT ("/")
//    for (int i = 0; i < rows - 2; i++)
//    {
//        for (int j = 2; j < cols; j++)
//        {
//            int val = grid[i][j];
//            if (val == -1)
//                continue;
//
//            if (grid[i + 1][j - 1] == val && grid[i + 2][j - 2] == val)
//            {
//                found = true;
//                int rr = i;
//                int cc = j;
//                int countMatch = 0;
//                while (rr < rows && cc >= 0 && grid[rr][cc] == val)
//                {
//                    removeCell[rr][cc] = true;
//                    rr++;
//                    cc--;
//                    countMatch++;
//                }
//                if (countMatch == 4)
//                {
//                    placeSpecial[i][j] = 6;
//                    removeCell[i][j] = false;
//                }
//                else if (countMatch >= 5)
//                {
//                    placeSpecial[i][j] = 7;
//                    removeCell[i][j] = false;
//                }
//                updateScore(countMatch);
//
//            }
//        }
//    }
//
//    for (int i = 0; i < rows; i++)
//        for (int j = 0; j < cols; j++)
//            if (placeSpecial[i][j] != -1)
//                grid[i][j] = placeSpecial[i][j];
//
//    return found;
//}
//
//void removeMatches(int grid[][max_col], bool removeCell[][max_col], int rows, int cols)
//{
//    for (int i = 0; i < rows; i++)
//        for (int j = 0; j < cols; j++)
//            if (removeCell[i][j])// means jn ko replace krna ha wo true hain
//                grid[i][j] = -1;// yh apply gravity ma jain gy 
//}
//
//
//void gravity(int grid[][max_col], int rows, int cols)
//// is ffunction sa ham grid=-1 wali ko upr ly ayn gy or candies ko nchy
//{
//    for (int j = 0; j < cols; j++)
//    {   // yh loop candies k lye ha
//        int end = rows - 1; // e.g if row size is 9 ... then it will store at 8 because of array indexing
//        for (int i = rows - 1; i >= 0; i--)
//        {
//            if (grid[i][j] != -1)
//            {
//                grid[end][j] = grid[i][j];
//                end--;
//            }
//        }
//        // yh loop candies k bd upper portion ma remove krny wli candies rkhy ga 
//        for (int i = end; i >= 0; i--)
//            grid[i][j] = -1;
//    }
//}
//
//void refillBoard(int grid[][max_col], int rows, int cols)
//{
//    for (int r = 0; r < rows; r++)
//        for (int c = 0; c < cols; c++)
//            if (grid[r][c] == -1)
//                grid[r][c] = rand() % 6;
//}
//
//void activateSpecial(int grid[][max_col], int rows, int cols, int rClick, int cClick)
//{
//    int val = grid[rClick][cClick];
//    if (val != 6 && val != 7) return;
//
//    if (val == 6)
//    {
//
//        for (int i = -1; i <= 1; i++)
//            for (int j = -1; j <= 1; j++)
//            {
//                int nr = rClick + i;// for boundries of 3x3
//                int nc = cClick + j;
//                if (nr >= 0 && nr < rows && nc >= 0 && nc < cols)
//                    grid[nr][nc] = -1;//3x3 ko -1 kr dy ga
//            }
//        score = score + 50; // small bonus for using special (optional)
//    }
//    else if (val == 7)
//    {
//        // clear entire row and column
//        for (int i = 0; i < rows; i++)
//            grid[i][cClick] = -1;
//        for (int j = 0; j < cols; j++)
//            grid[rClick][j] = -1;
//
//        score = score + 100;
//    }
//
//}
//
//void showHowToPlay()
//{
//    RenderWindow window(VideoMode(600, 500), "How to Play", Style::Titlebar | Style::Close);
//    Font f;
//    if (!f.loadFromFile("arial.ttf"))
//        cout << "FONT ERROR!\n";
//
//    Text instructions[8];
//    const char* instrText[8] = {
//        "1. you can swap adjacent candies ",
//        "2. matches can be horizontal,verticle or diagnol ",
//        "3. matched candies will be replaced with new candies",
//        "4. 3-match = 10 points, 4-match = 20 points, match>=5 = 30 points",
//        "5. 4-match creates a special candy 3x3 explosion on click.",
//        "6. 5+-match creates a special candy clears row & column on click.",
//        "7. Click SAVE to save game progress ",
//        "8. Win by reaching score in limited moves ",
//    };
//    for (int i = 0; i < 8; i++)
//    {
//        instructions[i].setFont(f);
//        instructions[i].setCharacterSize(18);
//        instructions[i].setFillColor(Color::White);
//        instructions[i].setString(instrText[i]);
//        instructions[i].setPosition(20, 20 + i * 45);
//    }
//
//    RectangleShape bg(Vector2f(600, 500));
//    bg.setFillColor(Color(80, 80, 80));
//
//    while (window.isOpen())
//    {
//        Event ev;
//        while (window.pollEvent(ev))
//        {
//            if (ev.type == Event::Closed || (ev.type == Event::MouseButtonPressed && ev.mouseButton.button == Mouse::Left))
//            {
//                window.close();
//            }
//        }
//
//        window.clear();
//        window.draw(bg);
//        for (int i = 0; i < 8; i++)
//            window.draw(instructions[i]);
//
//        window.display();
//    }
//}
//void swapCandies(int grid[][max_col], int row1, int col1, int row2, int col2) {
//    int temp = grid[row1][col1];
//    grid[row1][col1] = grid[row2][col2];
//    grid[row2][col2] = temp;
//}
//
//bool removeCell[max_row][max_col];
//int placeSpecial[max_row][max_col];
//void runGame(int grid[][max_col], int rows, int cols, bool condition)
//{
//    srand(static_cast<unsigned>(time(nullptr)));//asks the computer for the current time in seconds in order to give random values
//
//    int winW = cols * cellSize;
//    int winH = rows * cellSize + 150;
//
//    RenderWindow window(VideoMode(winW, winH), "Match-3 Candy Crush");
//
//    // used in findMatches signature
//
//    if (condition) {
//        for (int r = 0; r < rows; r++)
//            for (int c = 0; c < cols; c++)
//                grid[r][c] = rand() % 6;
//        InitialBoard(grid, rows, cols);
//    }
//    Texture textures[8];
//    for (int i = 0; i < 8; i++)
//    {
//
//
//        string filename = "candy" + to_string(i) + ".png";
//
//        if (!textures[i].loadFromFile(filename))
//        {
//            std::cout << "Error loading " << filename << "\n";
//            return;
//        }
//    }
//
//    if (!gameFont.loadFromFile("arial.ttf"))
//        cout << "FONT ERROR!\n";
//
//    loadingsounds();
//
//    // SAVE BUTTON
//    RectangleShape saveButton(Vector2f(150, 50));
//    saveButton.setFillColor(Color(52, 152, 219)); // Modern blue
//    saveButton.setOutlineThickness(4);
//    saveButton.setOutlineColor(Color(41, 128, 185)); // Darker blue outline
//    saveButton.setPosition(winW - 170, winH - 110);
//
//    Text saveText;
//    saveText.setFont(gameFont);
//    saveText.setString("SAVE");
//    saveText.setCharacterSize(28);
//    saveText.setFillColor(Color::White);
//    saveText.setPosition(winW - 135, winH - 100);
//
//    bool firstSelected = false;
//    int firstRow = -1, firstCol = -1;
//
//    while (window.isOpen())
//    {
//        if (gameOver)
//        {
//            window.close();
//            return;
//        }
//
//        Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == Event::Closed)
//                window.close();
//
//            if (!gameOver && event.type == Event::MouseButtonPressed &&
//                event.mouseButton.button == Mouse::Left)
//            {
//                int mx = event.mouseButton.x;
//                int my = event.mouseButton.y;
//
//                // SAVE BUTTON CLICK
//                if (saveButton.getGlobalBounds().contains((float)mx, (float)my)) {
//                    save(grid, rows, cols);
//                    window.close(); // close game window
//                    cout << "Game Saved!\n";
//                    return; // back to main menu
//                }
//
//                if (my > rows * cellSize) continue;
//
//                int i = my / cellSize;
//                int j = mx / cellSize;
//
//                if (i < 0 || i >= rows || j < 0 || j >= cols)
//                    continue;
//
//                int clickedVal = grid[i][j];
//
//                if (!firstSelected && (clickedVal == 6 || clickedVal == 7))
//                {
//
//                    // Activate special
//                    activateSpecial(grid, rows, cols, i, j);
//                    remainingmoves--;
//                    juicysound.play();
//
//                    // gravity/refill and cascade matches
//                    while (true)
//                    {
//                        removeMatches(grid, removeCell, rows, cols);
//                        gravity(grid, rows, cols);
//                        refillBoard(grid, rows, cols);
//
//
//                        if (!scanMatches(grid, removeCell, placeSpecial, rows, cols))
//                            break;
//
//
//                        removeMatches(grid, removeCell, rows, cols);
//                        gravity(grid, rows, cols);
//                        refillBoard(grid, rows, cols);
//                    }
//
//                    if (score >= targetgoal || remainingmoves <= 0)
//                    {
//                        gameOver = true;
//                        window.close();
//                        showEndWindow(score >= targetgoal, score);
//                        return;
//                    }
//
//                    continue; // processed click
//                }
//
//                if (!firstSelected)
//                {
//                    firstSelected = true;
//                    firstRow = i;
//                    firstCol = j;
//                }
//                else
//                {
//
//                    if (!isAdjacent(firstRow, firstCol, i, j)) {
//                        firstSelected = false;
//                        continue;
//                    }
//                    swapCandies(grid, firstRow, firstCol, i, j);
//                    // after swap, check matches
//                    bool matchHappened = scanMatches(grid, removeCell, placeSpecial, rows, cols);
//
//                    if (!matchHappened)
//                    {
//                        swapCandies(grid, firstRow, firstCol, i, j);
//
//                    }
//                    else
//                    {
//                        swapSound.play();
//                        remainingmoves--;
//
//                        // remove matches and cascade until no more
//                        while (true)
//                        {
//                            removeMatches(grid, removeCell, rows, cols);
//                            gravity(grid, rows, cols);
//                            refillBoard(grid, rows, cols);
//
//                            if (!scanMatches(grid, removeCell, placeSpecial, rows, cols))
//                                break;
//                        }
//                    }
//
//                    if (shouldEndGame())
//                    {
//                        gameOver = true;
//                        window.close();
//                        showEndWindow(score >= targetgoal, score);
//                        return;
//                    }
//
//                    firstSelected = false;
//                }
//            }
//        }
//
//        window.clear(Color::White);
//
//        for (int i = 0; i < rows; i++)
//        {
//            for (int j = 0; j < cols; j++)
//            {
//                int val = grid[i][j];
//                if (val < 0 || val >= 8) continue;
//
//                Sprite sp;
//                sp.setTexture(textures[val]);
//                float scaleX = (float)cellSize / textures[val].getSize().x;
//                float scaleY = (float)cellSize / textures[val].getSize().y;
//                sp.setScale(scaleX, scaleY);
//                sp.setPosition(j * cellSize, i * cellSize);
//                window.draw(sp);
//            }
//        }
//
//        if (firstSelected)
//        {
//            RectangleShape box(Vector2f(cellSize, cellSize));
//            box.setPosition(firstCol * cellSize, firstRow * cellSize);
//            box.setFillColor(Color(100, 205, 0, 103));
//            window.draw(box);
//        }
//        // left moves ,score k lye 
//        Text scoreTextDisplay;
//        scoreTextDisplay.setFont(gameFont);
//
//        string scoreString = "Score: " + to_string(score) + "  Target: " + to_string(targetgoal);
//
//        scoreTextDisplay.setString(scoreString);
//        scoreTextDisplay.setCharacterSize(28);
//        scoreTextDisplay.setFillColor(Color::Black);
//        scoreTextDisplay.setPosition(10, rows * cellSize + 10);
//        window.draw(scoreTextDisplay);
//
//        Text movesText;
//        movesText.setFont(gameFont);
//
//        string movesString = "Moves Left: " + to_string(remainingmoves);
//
//        movesText.setString(movesString);
//        movesText.setCharacterSize(35);
//        movesText.setFillColor(Color::Black);
//        movesText.setPosition(10, rows * cellSize + 55);
//        window.draw(movesText);
//
//        window.draw(saveButton);
//        window.draw(saveText);
//
//        window.display();
//    }
//}
//
//void hovereffect(RectangleShape& btn, Vector2i mousePos)
//{
//    if (btn.getGlobalBounds().contains((float)mousePos.x, (float)mousePos.y))
//        btn.setFillColor(Color(90, 150, 255));
//    else
//        btn.setFillColor(Color(70, 120, 220));
//}
//
//void Setmenu()
//{
//    if (!font.loadFromFile("arial.ttf"))
//        cout << "FONT ERROR!\n";
//
//    //TITLE
//    titleText.setFont(font);
//    titleText.setString("Candy Crush");
//    titleText.setCharacterSize(70);
//    titleText.setFillColor(Color(80, 40, 150));
//    titleText.setPosition(120, 25);
//
//    // ---------- START BUTTON ----------
//    startBtn.setPosition(175, 125);
//    startBtn.setSize(Vector2f(250, 60));
//    startBtn.setFillColor(Color(100, 149, 237));
//    startBtn.setOutlineThickness(5);
//    startBtn.setOutlineColor(Color(65, 105, 225));
//
//    startText.setFont(font);
//    startText.setString("Start Game");
//    startText.setCharacterSize(30);
//    startText.setFillColor(Color::White);
//    startText.setPosition(215, 140);
//
//    // ---------- HOW TO PLAY ----------
//    howIcon.setPosition(175, 205);
//    howIcon.setSize(Vector2f(250, 60));
//    howIcon.setFillColor(Color(60, 179, 113));
//    howIcon.setOutlineThickness(5);
//    howIcon.setOutlineColor(Color(65, 105, 225));
//
//    howText.setFont(font);
//    howText.setString("How to Play");
//    howText.setCharacterSize(30);
//    howText.setFillColor(Color::White);
//    howText.setPosition(210, 220);
//
//    // ---------- LOAD GAME ----------
//    loadBtn.setPosition(175, 285);
//    loadBtn.setSize(Vector2f(250, 60));
//    loadBtn.setFillColor(Color(135, 206, 235));
//    loadBtn.setOutlineThickness(5);
//    loadBtn.setOutlineColor(Color(65, 105, 225));
//
//    loadText.setFont(font);
//    loadText.setString("Load Game");
//    loadText.setCharacterSize(30);
//    loadText.setFillColor(Color::White);
//    loadText.setPosition(215, 300);
//
//    // ---------- EXIT ----------
//    exitBtn.setPosition(175, 365);
//    exitBtn.setSize(Vector2f(250, 60));
//    exitBtn.setFillColor(Color(255, 99, 71));
//    exitBtn.setOutlineThickness(5);
//    exitBtn.setOutlineColor(Color(65, 105, 225));
//
//    exitText.setFont(font);
//    exitText.setString("Exit");
//    exitText.setCharacterSize(30);
//    exitText.setFillColor(Color::White);
//    exitText.setPosition(245, 380);
//}
//
//void drawGradient(RenderWindow& window)
//{
//    VertexArray back(Quads, 4);
//
//    float w = 600;
//    float h = 600;
//
//    // Top-left
//    back[0].position = Vector2f(0, 0);
//    back[0].color = Color(120, 170, 255); // soft blue
//
//    // Top-right
//    back[1].position = Vector2f(w, 0);
//    back[1].color = Color(255, 190, 230); // gentle pink
//
//    // Bottom-right
//    back[2].position = Vector2f(w, h);
//    back[2].color = Color(190, 160, 255); // soft lavender
//
//    // Bottom-left
//    back[3].position = Vector2f(0, h);
//    back[3].color = Color(140, 230, 255); // pastel cyan
//
//    window.draw(back);
//}
//bool showDifficultyWindow(int& outRows, int& outCols)
//{
//    RenderWindow difficulty(VideoMode(700, 600), "Select Grid Size", Style::Titlebar | Style::Close);
//    Font f;
//    if (!f.loadFromFile("arial.ttf"))
//        cout << "FONT ERROR!\n";
//
//    // Title Text
//    Text titleText;
//    titleText.setFont(f);
//    titleText.setString("Select Grid Size");
//    titleText.setCharacterSize(55);
//    titleText.setFillColor(Color(255, 215, 0)); // Gold color
//    titleText.setPosition(160, 40);
//
//    // Buttons with new sizes and positions
//    RectangleShape easyBtn(Vector2f(400, 85));
//    RectangleShape medBtn(Vector2f(400, 85));
//    RectangleShape hardBtn(Vector2f(400, 85));
//
//    easyBtn.setPosition(150, 160);
//    medBtn.setPosition(150, 280);
//    hardBtn.setPosition(150, 400);
//
//    // Vibrant colors with outlines
//    easyBtn.setFillColor(Color(46, 213, 115)); // Emerald green
//    easyBtn.setOutlineThickness(5);
//    easyBtn.setOutlineColor(Color(25, 181, 94));
//
//    medBtn.setFillColor(Color(255, 159, 64)); // Vibrant orange
//    medBtn.setOutlineThickness(5);
//    medBtn.setOutlineColor(Color(230, 126, 34));
//
//    hardBtn.setFillColor(Color(255, 71, 87)); // Hot red
//    hardBtn.setOutlineThickness(5);
//    hardBtn.setOutlineColor(Color(235, 47, 68));
//
//    // Button texts
//    Text easyText("Small Grid (6 x 6)", f, 32);
//    easyText.setFillColor(Color::White);
//    easyText.setPosition(220, 180);
//
//    Text medText("Medium Grid (8 x 8)", f, 32);
//    medText.setFillColor(Color::White);
//    medText.setPosition(195, 300);
//
//    Text hardText("Large Grid (10 x 10)", f, 32);
//    hardText.setFillColor(Color::White);
//    hardText.setPosition(190, 420);
//
//    while (difficulty.isOpen())
//    {
//        Event e;
//        while (difficulty.pollEvent(e))
//        {
//            if (e.type == Event::Closed)
//            {
//                difficulty.close();
//                return false;
//            }
//
//            if (e.type == Event::MouseButtonPressed && e.mouseButton.button == Mouse::Left)
//            {
//                Vector2i m(e.mouseButton.x, e.mouseButton.y);
//
//                if (easyBtn.getGlobalBounds().contains((float)m.x, (float)m.y))
//                {
//                    outRows = 6; outCols = 6;
//                    setTarget(outRows, outCols);
//                    difficulty.close();
//                    return true;
//                }
//                if (medBtn.getGlobalBounds().contains((float)m.x, (float)m.y))
//                {
//                    outRows = 8; outCols = 8;
//                    setTarget(outRows, outCols);
//                    difficulty.close();
//                    return true;
//                }
//                if (hardBtn.getGlobalBounds().contains((float)m.x, (float)m.y))
//                {
//                    outRows = 10; outCols = 10;
//                    setTarget(outRows, outCols);
//                    difficulty.close();
//                    return true;
//                }
//            }
//        }
//
//        difficulty.clear(Color(44, 62, 80)); // Dark blue-grey background
//        difficulty.draw(titleText);
//        difficulty.draw(easyBtn);
//        difficulty.draw(medBtn);
//        difficulty.draw(hardBtn);
//        difficulty.draw(easyText);
//        difficulty.draw(medText);
//        difficulty.draw(hardText);
//        difficulty.display();
//    }
//
//    return false;
//}
//void backgroundmusic(Music& music)
//{
//    if (!music.openFromFile("themesong.mp3"))
//    {
//        cout << "Music Error: Check filename/folder!\n";
//    }
//    else
//    {
//        music.setLoop(true);
//        music.setVolume(50);
//        music.play();
//    }
//}
//void resetGame() {
//    score = 0;
//    remainingmoves = 20;
//    gameOver = false;
//}
//int main()
//{
//    RenderWindow window(VideoMode(600, 600), "Main Menu");
//
//    Setmenu();
//    Music bgMusic;
//    backgroundmusic(bgMusic);
//    while (window.isOpen()) {
//
//
//        Event e;
//        while (window.pollEvent(e))
//        {
//            if (e.type == Event::Closed)
//                window.close();
//
//            int grid[max_row][max_col];
//            bool condition = false;
//
//            if (e.type == Event::MouseButtonPressed && e.mouseButton.button == Mouse::Left)
//            {
//                Vector2i m(e.mouseButton.x, e.mouseButton.y);
//
//                if (startBtn.getGlobalBounds().contains((float)m.x, (float)m.y))
//                {
//                    resetGame();//--- score =0,moves20 ...
//                    condition = true;
//                    int chosenRows = 0, chosenCols = 0;
//
//                    window.setVisible(false);
//                    bool ok = showDifficultyWindow(chosenRows, chosenCols);
//                    window.setVisible(!ok);
//
//                    if (ok && chosenRows > 0 && chosenCols > 0)
//                    {
//                        bgMusic.stop();
//                        runGame(grid, chosenRows, chosenCols, condition);
//                        bgMusic.play();
//                        window.create(VideoMode(600, 600), "Main Menu");
//                        Setmenu();
//                    }
//                }
//
//                if (howIcon.getGlobalBounds().contains((float)m.x, (float)m.y))
//                {
//                    showHowToPlay();
//                }
//
//                if (loadBtn.getGlobalBounds().contains((float)m.x, (float)m.y))
//                {
//                    int rows, cols;
//                    if (load(grid, rows, cols))
//                    {
//
//                        setTarget(rows, cols);
//
//                        window.setVisible(false);
//                        bgMusic.stop();
//                        runGame(grid, rows, cols, condition);
//                        bgMusic.play();
//                        window.create(VideoMode(600, 600), "Main Menu");
//                        Setmenu();
//                    }
//                }
//
//                if (exitBtn.getGlobalBounds().contains((float)m.x, (float)m.y))
//                    window.close();
//            }
//        }
//
//        Vector2i mousePos = Mouse::getPosition(window);
//        hovereffect(startBtn, mousePos);
//        hovereffect(exitBtn, mousePos);
//        hovereffect(howIcon, mousePos);
//        hovereffect(loadBtn, mousePos);
//
//        drawGradient(window);
//
//        window.draw(titleText);
//        window.draw(startBtn);
//        window.draw(startText);
//        window.draw(howIcon);
//        window.draw(howText);
//        window.draw(exitBtn);
//        window.draw(exitText);
//        window.draw(loadBtn);
//        window.draw(loadText);
//
//        window.display();
//    }
//
//    return 0;
//}
//
