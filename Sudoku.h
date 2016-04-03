

class Sudoku{
	public:
		Sudoku();

		void giveQuestion();
		void readIn();
		void solve();
		void changeNum(int a,int b);
		void changeRow(int a,int b);
		void changeCol(int a,int b);
		void rotate(int n);
		void flip(int n);
		void transform();
		void printOut(bool,int a[81]);
	private:

		int q[81];
//		int map[81];
		int RowRecord[2];
		int ColRecord[2];

		void change();
	
		//solving technique
		void TurnOffOrigin(bool a[81][9],int q[81]);
		void CheckSmlMatrix(bool a[81][9],int q[81]);
		void CheckRow(bool a[81][9],int q[81]);
		void CheckCol(bool a[81][9],int q[81]);
		void OnlyRemain(bool a[81][9],int q[81]);
		void Refill(bool a[81][9],int q[81]);
		void TraceBack(int n,bool l[81][9],int a[81]);
//		void RemainTry();

		bool CheckMap(int map[81]);
};

