namespace AdvantOfCode.day04;

public class Day04 : Solution
{
    private class Board
    {
        private (int,int) LastMark { get; set; }
        private int LastNum { get; set; }
        private const int BoardSize = 5;
        private const int Marked = -1;
        private int[][] _board;
        
        public Board(string[] lines)
        {
            _board = new int[BoardSize][];
            for (int i = 0; i < BoardSize ; ++i)
            {
                _board[i] = new int[BoardSize];
                string[] line = lines[i].Split(' ', StringSplitOptions.RemoveEmptyEntries);
                for (int j = 0; j < BoardSize; ++j)
                {
                    _board[i][j] = Convert.ToInt32(line[j]);
                }
            }
        }

        public bool MarkNum(int num)
        {
            for (int i = 0; i < BoardSize; ++i)
            {
                for (int j = 0; j < BoardSize; ++j)
                {
                    if (_board[i][j] == num)
                    {
                        _board[i][j] = Marked;
                        LastMark = (i, j);
                        LastNum = num;
                        return true;
                    }
                }
            }

            return false;
        }

        public bool CheckForWin()
        {
            // Check for a row win
            for (int j = 0; j < BoardSize; ++j)
            {
                if (_board[LastMark.Item1][j] != Marked)
                {
                    break;
                }
                else if (j == (BoardSize - 1))
                {
                    return true;
                }
            }
            
            // Check for a col win
            for (int j = 0; j < BoardSize; ++j)
            {
                if (_board[j][LastMark.Item2] != Marked)
                {
                    break;
                }
                else if (j == (BoardSize - 1))
                {
                    return true;
                }
            }

            return false;
        }

        private int SumOfUnmarked()
        {
            int sum = 0;
            foreach (int[] line in _board)
            {
                foreach (int entry in line)
                {
                    if (entry != Marked)
                    {
                        sum += entry;
                    }
                }
            }

            return sum;
        }

        public int GetScore()
        {
            return SumOfUnmarked() * LastNum;
        }
    }

    private List<Board> InitializeBoards(string[] lines)
    {
        List<Board> boards = new List<Board>();
        for (int i = 0; i < lines.Length - 1; i += 5)
        {
            string[] board = new string[5];
            Array.Copy(lines, i+1, board, 0, 5);
            boards.Add(new Board(board));
        }

        return boards;
    }

    // Runs the Bingo numbers and returns the winner
    private Board RunBingoNumbers(string input, List<Board> boards)
    {
        string[] numbers = input.Split(",", StringSplitOptions.RemoveEmptyEntries);

        foreach (string number in numbers)
        {
            int currNum = Convert.ToInt32(number);
            foreach (Board board in boards)
            {
                bool marked = board.MarkNum(currNum);
                if (!marked)
                {
                    continue;
                }

                if (board.CheckForWin())
                {
                    return board;
                }
            }
        }

        return null;
    }
    public string SolvePartOne(string filePath)
    {
        string[] lines = Util.ParseInput(filePath);
        List<Board> boards = InitializeBoards(lines);
        Board winningBoard = RunBingoNumbers(lines[0], boards);
        int res = winningBoard.GetScore();
        return res.ToString();
    }

    private Board GetLastWinningBoard(string bingoNumbers, List<Board> boards)
    {
        int numOfBoards = boards.Count;
        for (int i = 0; i < numOfBoards - 1; ++i)
        {
            Board board = RunBingoNumbers(bingoNumbers, boards);
            boards.Remove(board);
        }

        RunBingoNumbers(bingoNumbers, boards);

        return boards[0];
    }
    public string SolvePartTwo(string filePath)
    {
        string[] lines = Util.ParseInput(filePath);
        List<Board> boards = InitializeBoards(lines);
        Board lastWinningBoard = GetLastWinningBoard(lines[0], boards);
        return lastWinningBoard.GetScore().ToString();
    }
}