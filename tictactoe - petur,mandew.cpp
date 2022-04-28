int analogPin0 = 0, analogPin1 = 0, analogPin2 = 0;
int gameBoard[3][3] = { {0,1,0},{0,0,0},{0,2,0} };
int turn = 1;
int movesCount = 1;
int gamemode = 0;
bool firstMove = true;
int playerTurn = 1;


void setup()
{
	randomSeed(analogRead(0));
	turn = random(1, 3);
	for (int i = 0; i <= 12; i++)
	{
		pinMode(i, OUTPUT);
		if (i >= 2 && i < 11)
		{
			digitalWrite(i, HIGH);
		}
	}
	pinMode(13, INPUT);
}

void loop()
{
	while (gamemode == 0)
	{
		DrawBoard();
		ChooseGamemode();
	}
	if (gamemode == 2)
	{
		DrawBoard();
		GetInput();
		CheckForWin();
	}
	else if (gamemode == 1)
	{
		if (turn == playerTurn)
		{
			DrawBoard();
			GetInput();
			CheckForWin();
		}
		else
		{
			DrawBoard();
			AITurn();
			CheckForWin();
		}
	}
	else if (gamemode == 3)
	{
		if (turn == playerTurn)
		{
			DrawBoard();
			GetInput();
			CheckForWin();
		}
		else
		{
			DrawBoard();
			RandomAIMove(3);
			CheckForWin();
		}
	}
	//DrawBoard();
	//GetInput();
	//CheckForWin();
}

void ChooseGamemode()
{
	analogPin1 = analogRead(1);
	if (analogPin1 < 60)
	{
		playerTurn = 1;
		turn = 1;
		gamemode = 1;
		ChangeAllBoard(0);
		DrawBoard();
		delay(100);

	}
	else if (analogPin1 < 200)
	{
		gamemode = 2;
		ChangeAllBoard(0);
		DrawBoard();
		delay(100);
	}
	else if (analogPin1 < 400)
	{
		playerTurn = 1;
		turn = 1;
		gamemode = 3;
		ChangeAllBoard(0);
		DrawBoard();
		delay(100);
	}
}

void DrawBoard()
{
	int pinIndex;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{

			if (gameBoard[i][j] == 1)
			{
				pinIndex = 11 - (j * 3 + i + 1);
				digitalWrite(pinIndex, LOW);
				digitalWrite(0, HIGH);
			}
			else if (gameBoard[i][j] == 2)
			{
				pinIndex = 11 - (j * 3 + i + 1);
				digitalWrite(pinIndex, LOW);
				digitalWrite(1, HIGH);
			}
			else
			{

			}
			digitalWrite(pinIndex, HIGH);
			digitalWrite(0, LOW);
			digitalWrite(1, LOW);
		}
	}
	if (turn == 1)
	{
		digitalWrite(11, HIGH);
		digitalWrite(12, LOW);
	}
	if (turn == 2)
	{
		digitalWrite(11, LOW);
		digitalWrite(12, HIGH);
	}
}

void GetInput()
{
	analogPin0 = analogRead(0);
	analogPin1 = analogRead(1);
	analogPin2 = analogRead(2);

	if (analogPin0 < 60)
	{

		if (gameBoard[0][0] == 0)
		{
			movesCount++;
			gameBoard[0][0] = turn;
			turn = 3 - turn;
		}
		Serial.println("1");
		return;
	}
	else if (analogPin0 < 200)
	{
		if (gameBoard[1][0] == 0)
		{
			movesCount++;
			gameBoard[1][0] = turn;
			turn = 3 - turn;
		}
		Serial.println("2");
		return;
	}
	else if (analogPin0 < 400)
	{
		if (gameBoard[2][0] == 0)
		{
			movesCount++;
			gameBoard[2][0] = turn;
			turn = 3 - turn;
		}
		Serial.println("3");
		return;
	}
	if (analogPin1 < 60)
	{
		if (gameBoard[0][1] == 0)
		{
			movesCount++;
			gameBoard[0][1] = turn;
			turn = 3 - turn;
		}
		Serial.println("4");
		return;
	}
	else if (analogPin1 < 200)
	{
		if (gameBoard[1][1] == 0)
		{
			movesCount++;
			gameBoard[1][1] = turn;
			turn = 3 - turn;
		}
		Serial.println("5");
		return;
	}
	else if (analogPin1 < 400)
	{
		if (gameBoard[2][1] == 0)
		{
			movesCount++;
			gameBoard[2][1] = turn;
			turn = 3 - turn;
		}
		Serial.println("6");
		return;
	}
	if (analogPin2 < 60)
	{
		if (gameBoard[0][2] == 0)
		{
			movesCount++;
			gameBoard[0][2] = turn;
			turn = 3 - turn;
		}
		Serial.println("7");
		return;
	}
	else if (analogPin2 < 200)
	{
		if (gameBoard[1][2] == 0)
		{
			movesCount++;
			gameBoard[1][2] = turn;
			turn = 3 - turn;
		}
		Serial.println("8");
		return;
	}
	else if (analogPin2 < 400)
	{
		if (gameBoard[2][2] == 0)
		{
			movesCount++;
			gameBoard[2][2] = turn;
			turn = 3 - turn;
		}
		Serial.println("9");
		return;
	}
}
void CheckForWin()
{
	for (int i = 0; i <= 2; i++)
	{
		if (gameBoard[i][0] == gameBoard[i][1] && gameBoard[i][1] == gameBoard[i][2])
		{
			if (gameBoard[i][0] != 0)
			{
				turn = 3 - turn;
				BlinkBoard(2);
				ChangeAllBoard(turn);
				BlinkBoard(2);
				ResetGame();
			}
		}
	}
	for (int i = 0; i <= 2; i++)
	{
		if (gameBoard[0][i] == gameBoard[1][i] && gameBoard[1][i] == gameBoard[2][i])
		{
			if (gameBoard[0][i] != 0)
			{
				turn = 3 - turn;
				BlinkBoard(2);
				ChangeAllBoard(turn);
				BlinkBoard(2);
				ResetGame();
			}
		}
	}
	if (gameBoard[0][0] == gameBoard[1][1] && gameBoard[1][1] == gameBoard[2][2])
	{
		if (gameBoard[0][0] != 0)
		{
			turn = 3 - turn;
			BlinkBoard(2);
			ChangeAllBoard(turn);
			BlinkBoard(2);
			ResetGame();
		}
	}

	if (gameBoard[0][2] == gameBoard[1][1] && gameBoard[1][1] == gameBoard[2][0])
	{
		if (gameBoard[0][2] != 0)
		{
			turn = 3 - turn;
			BlinkBoard(2);
			ChangeAllBoard(turn);
			BlinkBoard(2);
			ResetGame();
		}
	}

	if (movesCount == 10)
	{
		BlinkBoard(5);
		ResetGame();
	}
}

void ChangeAllBoard(int x)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			gameBoard[i][j] = x;
		}
	}
}

void BlinkBoard(int numberOfLoops)
{
	for (int j = 0; j <= numberOfLoops; j++)
	{
		for (int i = 0; i < 55; i++)
		{
			DrawBoard();
		}
		digitalWrite(0, LOW);
		digitalWrite(1, LOW);
		delay(150);
	}
}

void ResetGame()
{
	ChangeAllBoard(0);
	gameBoard[0][1] = 1;
	gameBoard[2][1] = 2;
	turn = 1;
	movesCount = 0;
	gamemode = 0;
	firstMove = true;
}


bool checkMovesLeft(int gBoard[3][3])                //Function to check if there are still empty spaces on the board
{
	for (int i = 0; i <= 2; i++)                           //Loop through all 9 board positions - i row, j column
		for (int j = 0; j <= 2; j++)
			if (gBoard[i][j] == 0)
				return true;                                  //If an empty space is found, return true
	return false;
}

int EvaluateBoard(int gBoard[3][3])                                         //Function to evaluate the current board value
{
	for (int i = 0; i <= 2; i++)                                              //Loop through all rows and check for a win
	{
		if (gBoard[i][0] == gBoard[i][1] && gBoard[i][1] == gBoard[i][2])
		{
			if (gBoard[i][0] == 1)
				return 10;
			else if (gBoard[i][0] == 2)
				return -10;
		}
	}
	for (int j = 0; j <= 2; j++)                                              //Loop through all columns and check for a win
	{
		if (gBoard[0][j] == gBoard[1][j] && gBoard[1][j] == gBoard[2][j])
		{
			if (gBoard[0][j] == 1)
				return 10;
			else if (gBoard[0][j] == 2)
				return -10;
		}
	}
	if (gBoard[0][0] == gBoard[1][1] && gBoard[1][1] == gBoard[2][2])      //Check first diagonal for a win
	{
		if (gBoard[0][0] == 1)
			return 10;
		else if (gBoard[0][0] == 2)
			return -10;
	}
	if (gBoard[0][2] == gBoard[1][1] && gBoard[1][1] == gBoard[2][0])      //Check second diagonal for a win
	{
		if (gBoard[0][2] == 1)
			return 10;
		else if (gBoard[0][2] == 2)
			return -10;
	}
	return 0;
}

int MiniMaxAlgorithm(int gBoard[3][3], int depth, int alpha, int beta, bool isMax)            //Considers the possible plays and returns a value for the current board position
{
	int score = EvaluateBoard(gBoard);

	if (score == 10 || score == -10)                                //If a player has won the game
		return score;

	if (checkMovesLeft(gBoard) == false)                           //If there are no moves left then it must be a draw
		return 0;

	if (isMax)                                                      //If this is the maximizer's turn
	{
		int best = -1000;
		for (int i = 0; i <= 2; i++)                                      //Go through each cell
			for (int j = 0; j <= 2; j++)
				if (gBoard[i][j] == 0)                                    //If the space hasn't been played
				{
					gBoard[i][j] = 1;                                       //Play the move
					best = max(best, MiniMaxAlgorithm(gBoard, depth + 1, alpha, beta, !isMax));
					gBoard[i][j] = 0;
					alpha = max(alpha, best);
					if (beta <= alpha) break;
					//Undo the move
				}
		return best;
	}
	else                                                            //If this is the minimizer's turn
	{
		int best = 1000;
		for (int i = 0; i <= 2; i++)                                     //Go through each cell
			for (int j = 0; j <= 2; j++)
				if (gBoard[i][j] == 0)                                    //If the space hasn't been played
				{
					gBoard[i][j] = 2;                                       //Play the move
					best = min(best, MiniMaxAlgorithm(gBoard, depth + 1, alpha, beta, !isMax));
					gBoard[i][j] = 0; //Undo the move
					beta = min(beta, best);
					if (beta <= alpha) break;
				}
		return best;
	}
}

void AITurn()
{
	int bestRow = 0;
	int bestCol = 0;
	if (firstMove)
	{
		bool played = false;                                       //Check for whether AI has found an unoccupied corner
		int temp = random(4);
		if (temp == 0)
		{
			if (gameBoard[0][0] == 0)
			{
				bestRow = 0;
				bestCol = 0;
				played = true;
			}
		}
		else if (temp == 1)
		{
			if (gameBoard[0][2] == 0)
			{
				bestRow = 0;
				bestCol = 2;
				played = true;
			}
		}
		else if (temp == 2)
		{
			if (gameBoard[2][0] == 0)
			{
				bestRow = 2;
				bestCol = 0;
				played = true;
			}
		}
		else
		{
			if (gameBoard[2][2] == 0)
			{
				bestRow = 2;
				bestCol = 2;
				played = true;
			}
		}
		if (!played)
		{
			bestRow = 1;
			bestCol = 1;
		}
		firstMove = false;
	}
	else
	{
		int bestVal = +1000;
		for (int i = 0; i <= 2; i++)                                    //Go through each cell
			for (int j = 0; j <= 2; j++)
				if (gameBoard[i][j] == 0)                               //If the space hasn't been played
				{
					gameBoard[i][j] = turn;                                  //Play the move
					int moveVal = MiniMaxAlgorithm(gameBoard, 0, -1000, +1000, true);
					gameBoard[i][j] = 0;                                  //Undo the move
					if (moveVal < bestVal)
					{
						bestRow = i;
						bestCol = j;
						bestVal = moveVal;
					}


				}
	}
	movesCount++;
	gameBoard[bestRow][bestCol] = 2;                            //Once all combinations have been explored, play the best move
	turn = 3 - turn;                                                   //Set back to player's turn
}

void RandomAIMove(int randomMoves)
{
	bool played = false;                                         //Check to see that a move has been played
	if (movesCount < randomMoves)
	{
		while (!played)
		{
			int randomPos = random(9);                               //Generate a random board position
			switch (randomPos)                                       //Check position is unoccupied then play the random position
			{
			case 1:
				if (gameBoard[0][0] == 0)
				{
					gameBoard[0][0] = 2;
					played = true;
				}
				break;
			case 2:
				if (gameBoard[0][1] == 0)
				{
					gameBoard[0][1] = 2;
					played = true;
				}
				break;
			case 3:
				if (gameBoard[0][2] == 0)
				{
					gameBoard[0][2] = 2;
					played = true;
				}
				break;
			case 4:
				if (gameBoard[1][0] == 0)
				{
					gameBoard[1][0] = 2;
					played = true;
				}
				break;
			case 5:
				if (gameBoard[1][1] == 0)
				{
					gameBoard[1][1] = 2;
					played = true;
				}
				break;
			case 6:
				if (gameBoard[1][2] == 0)
				{
					gameBoard[1][2] = 2;
					played = true;
				}
				break;
			case 7:
				if (gameBoard[2][0] == 0)
				{
					gameBoard[2][0] = 2;
					played = true;
				}
				break;
			case 8:
				if (gameBoard[2][1] == 0)
				{
					gameBoard[2][1] = 2;
					played = true;
				}
				break;
			case 9:
				if (gameBoard[2][2] == 0)
				{
					gameBoard[2][2] = 2;
					played = true;
				}
				break;
			}
		}
		movesCount++;
		turn = 3 - turn;
	}
	else
	{
		AITurn();                                            //AI takes over after two turns so that it has a chance of winning and will complete "almost" lines
	}

	delay(50);
}

