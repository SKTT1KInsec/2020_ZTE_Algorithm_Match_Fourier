#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>
#include <ctime>


//输入与输出文件

#define INPUT_FILE_NAME "./Example.csv"
#define OUTPUT_FILE_NAME "./result.txt"


using namespace std;

//字符串转整数
inline int string_to_int(string str) {
	int i = 0, len = str.length();
	short int sum = 0;
	while (i < len) {
		sum = sum * 10 + str[i] - '0';
		i++;
	}
	return sum;
}

//从文件中读取字符串
inline void file_to_string(vector<string>& record, const string& line, char delimiter)
{
	int line_position = 0;
	char c;
	int line_max = line.length();
	string curstring;
	record.clear();
	while (line_position < line_max)
	{
		c = line[line_position];
		if (isdigit(c)) {
			curstring += c;
		}
		else if (c == delimiter && curstring.size()) {
			record.push_back(curstring);
			curstring = "";
		}
		line_position++;
	}
	if (curstring.size())
		record.push_back(curstring);
	return;
}

//从文件中读取矩阵
int matrix_read(
	vector<vector< short int> >& M_example,
	short int& ROW, short int& COLUMN) {


	vector<short int> M_example_temp;
	vector<string> str_row;
	string line;
	ifstream input_file(INPUT_FILE_NAME);

	if (input_file.fail()) {
		cout << "File not found" << endl;
		return -1;
	}

	while (getline(input_file, line) && input_file.good())
	{
		file_to_string(str_row, line, ',');
		for (int i = 0, Row_length = str_row.size(); i < Row_length; i++) {
			M_example_temp.push_back(string_to_int(str_row[i]));
		}
		M_example.push_back(M_example_temp);
		M_example_temp.clear();
		ROW++;
	}
	COLUMN = short int(str_row.size());
	input_file.close();
	return 0;
}

//搜索矩阵最大有效行数和列数
inline int Adjacency_Matrix_R_C_Max(
	vector<vector<short int>>& M_Example,
	short int& M_Example_Row_CNT_MAX,
	short int& M_Example_Column_CNT_MAX,
	short int& ROW, short int& COLUMN) {

	for (int i = 0; i < ROW; i++) {
		int M_Example_Row_CNT_temp = 0;
		for (int j = 0; j < COLUMN; j++) {
			if (M_Example[i][j] == 1) {
				M_Example_Row_CNT_temp++;
			}
		}
		if (M_Example_Row_CNT_temp > M_Example_Row_CNT_MAX)
			M_Example_Row_CNT_MAX = M_Example_Row_CNT_temp;
	}

	for (int j = 0; j < COLUMN; j++) {
		int M_Example_Column_CNT_temp = 0;
		for (int i = 0; i < ROW; i++) {
			if (M_Example[i][j] == 1) {
				M_Example_Column_CNT_temp++;
			}
		}
		if (M_Example_Column_CNT_temp > M_Example_Column_CNT_MAX)
			M_Example_Column_CNT_MAX = M_Example_Column_CNT_temp;
	}
	return 0;
}

//将邻接矩阵转为邻接表
int Adjacency_Matrix_TO_Adjacency_Table(
	vector<vector<short int>>& M_Example,
	vector<vector<short int>>& M_Example_Row,
	vector<vector<short int>>& M_Example_Column,
	short int& ROW, short int& COLUMN) {

	for (int i = 0; i < ROW; i++) {
		int M_Example_Row_CNT = 0;
		for (int j = 0; j < COLUMN; j++) {
			if (M_Example[i][j] == 1) {
				M_Example_Row[i][M_Example_Row_CNT] = j + 1;
				M_Example_Row_CNT++;
			}
		}
	}

	for (int j = 0; j < COLUMN; j++) {
		int M_Example_Column_CNT = 0;
		for (int i = 0; i < ROW; i++) {
			if (M_Example[i][j] == 1) {
				M_Example_Column[j][M_Example_Column_CNT] = i + 1;
				M_Example_Column_CNT++;
			}
		}
	}

	return 0;
}

//搜索名字为4个的祭品数量
int Fourier_4(
	vector<vector<short int>>& M_Example,
	vector<vector<short int>>& M_Example_Row,
	vector<vector<short int>>& M_Example_Column,
	short int& M_Example_Row_CNT_MAX,
	short int& M_Example_Column_CNT_MAX,
	short int& ROW, short int& COLUMN) {


	vector<int>Circle_4(ROW);
	vector<short int>ZEORS(M_Example_Row_CNT_MAX, 0);

	for (int i = 0; i < ROW; i++) {
		int Circle_4_cnt = 0;
		for (int j = 0; j < M_Example_Row_CNT_MAX - 1; j++) {
			short int Path1 = M_Example_Row[i][j];
			if (Path1 == 0)
				continue;
			for (int k = j + 1; k < M_Example_Row_CNT_MAX; k++) {
				short int Path4 = M_Example_Row[i][k];
				if (Path4 == 0)
					continue;
				for (int m = 0; m < M_Example_Column_CNT_MAX; m++) {
					short int Path2 = M_Example_Column[Path1 - 1][m];
					if (Path2 == 0 || Path2 == (i + 1) || M_Example_Row[Path2 - 1][0] == 0)
						continue;
					for (int n = 0; n < M_Example_Column_CNT_MAX; n++) {
						short int Path3 = M_Example_Column[Path4 - 1][n];
						if (Path3 == 0 || Path3 == (i + 1) || M_Example_Row[Path3 - 1][0] == 0)
							continue;
						if (Path2 == Path3) {
							Circle_4_cnt++;
						}
					}
				}
			}
		}
		Circle_4[i] = Circle_4_cnt;
		M_Example_Row[i] = ZEORS;
	}
	long result_Circle_4 = accumulate(Circle_4.begin(), Circle_4.end(), 0);
	return result_Circle_4;
}

//搜索名字为6个的祭品数量
int Fourier_6(
	vector<vector<short int>>& M_Example,
	vector<vector<short int>>& M_Example_Row,
	vector<vector<short int>>& M_Example_Column,
	short int& M_Example_Row_CNT_MAX,
	short int& M_Example_Column_CNT_MAX,
	short int& ROW, short int& COLUMN) {


	int SEQUENCE_MAX = M_Example_Row_CNT_MAX * M_Example_Row_CNT_MAX * M_Example_Column_CNT_MAX;

	vector<vector<short int>> Sequence(SEQUENCE_MAX, vector<short int>(3, 0));
	vector<vector<short int>> Sequence_Row(2, vector<short int>(2, 0));
	vector<vector<short int>> Sequence_Column(2, vector<short int>(3, 0));

	vector<short int>ZEORS(M_Example_Row_CNT_MAX, 0);
	int Repeated_Path_MAX = 0;
	vector<long>Circle_6_cnt(24, 0);


	for (int i = 0; i < ROW; i++) {

		int SEQUENCE_COUNT = 0;
		vector<int>NUMBER_SEQUENCE_PATH3(COLUMN, 0);

		for (int j = 0; j < M_Example_Row_CNT_MAX; j++) {
			short int Path1 = M_Example_Row[i][j];
			if (Path1 == 0)
				continue;
			for (int k = 0; k < M_Example_Column_CNT_MAX; k++) {
				short int Path2 = M_Example_Column[Path1 - 1][k];
				if (Path2 == 0 || Path2 == (i + 1))
					continue;
				for (int m = 0; m < M_Example_Row_CNT_MAX; m++) {
					short int Path3 = M_Example_Row[Path2 - 1][m];
					if (Path3 == 0 || Path3 == Path1)
						continue;
					Sequence[SEQUENCE_COUNT] = { Path1,Path2,Path3 };
					SEQUENCE_COUNT++;
				}
			}
		}



		for (int r = 0; r < SEQUENCE_COUNT; r++) {
			NUMBER_SEQUENCE_PATH3[Sequence[r][2] - 1]++;
		}

		int MAX_NUMBER_SEQUENCE_PATH3 = 0;

		for (int s = 0; s < COLUMN; s++) {
			if (NUMBER_SEQUENCE_PATH3[s] > MAX_NUMBER_SEQUENCE_PATH3)
				MAX_NUMBER_SEQUENCE_PATH3 = NUMBER_SEQUENCE_PATH3[s];
		}

		vector < vector<vector<short int>>>SEQUENCE_PATH3(COLUMN, vector < vector<short int>>(MAX_NUMBER_SEQUENCE_PATH3, vector<short int>(3, 0)));
		vector<int>NUMBER_SEQUENCE_PATH3_COUNT(COLUMN, 0);

		for (int t = 0; t < SEQUENCE_COUNT; t++) {
			SEQUENCE_PATH3[Sequence[t][2] - 1][NUMBER_SEQUENCE_PATH3_COUNT[Sequence[t][2] - 1]] = Sequence[t];
			NUMBER_SEQUENCE_PATH3_COUNT[Sequence[t][2] - 1]++;
		}

		for (int u = 0; u < COLUMN; u++) {
			if (NUMBER_SEQUENCE_PATH3[u] > 1) {
				for (int v = 0; v < NUMBER_SEQUENCE_PATH3[u]; v++) {
					for (int w = v + 1; w < NUMBER_SEQUENCE_PATH3[u]; w++) {
						if (SEQUENCE_PATH3[u][w][0] == SEQUENCE_PATH3[u][v][0])
							continue;
						if (SEQUENCE_PATH3[u][w][1] == SEQUENCE_PATH3[u][v][1])
							continue;
						int Repeated_Path = 0;
						Sequence_Row[0] = { SEQUENCE_PATH3[u][w][1],SEQUENCE_PATH3[u][v][1] };
						Sequence_Column[0] = { SEQUENCE_PATH3[u][w][0],SEQUENCE_PATH3[u][v][0],SEQUENCE_PATH3[u][w][2] };

						for (int Repeated_e = 0; Repeated_e < 3; Repeated_e++) {
							Sequence_Row[1] = { 1,1 };
							Sequence_Column[1] = { 1,1,1 };
							if (M_Example[i][Sequence_Column[0][Repeated_e] - 1] == 1) {
								Sequence_Column[1][Repeated_e] = 0;
								for (int Repeated_f = 0; Repeated_f < 3; Repeated_f++) {
									if (Sequence_Column[1][Repeated_f] == 0)
										continue;
									if (M_Example[i][Sequence_Column[0][Repeated_f] - 1] == 1) {
										Sequence_Column[1][Repeated_f] = 0;
										for (int Repeated_i = 0; Repeated_i < 2; Repeated_i++) {
											if (M_Example[Sequence_Row[0][Repeated_i] - 1][Sequence_Column[0][Repeated_e] - 1] == 1) {
												Sequence_Row[1][Repeated_i] = 0;
												for (int Repeated_j = 0; Repeated_j < 2; Repeated_j++) {
													if (Sequence_Row[1][Repeated_j] == 0)
														continue;
													if (M_Example[Sequence_Row[0][Repeated_j] - 1][Sequence_Column[0][Repeated_f] - 1] == 1) {
														Sequence_Row[1][Repeated_j] = 0;
														for (int Repeated_k = 0; Repeated_k < 3; Repeated_k++) {
															if (Sequence_Column[1][Repeated_k] == 0)
																continue;
															if (M_Example[Sequence_Row[0][Repeated_i] - 1][Sequence_Column[0][Repeated_k] - 1] == 1 && M_Example[Sequence_Row[0][Repeated_j] - 1][Sequence_Column[0][Repeated_k] - 1] == 1) {
																Sequence_Column[1][Repeated_k] = 0;
																Repeated_Path++;
															}
															Sequence_Column[1][Repeated_k] = 1;
														}
													}
													Sequence_Row[1][Repeated_j] = 1;
												}
											}
											Sequence_Row[1][Repeated_i] = 1;
										}
									}
									Sequence_Column[1][Repeated_f] = 1;
								}
							}
							Sequence_Column[1][Repeated_e] = 1;
						}
						if ((int(Repeated_Path) % 2) != 0)
							cout << "Repeated_Path Error:" << Repeated_Path << endl;
						else
							Repeated_Path = Repeated_Path / 2;
						if (Repeated_Path > Repeated_Path_MAX)
							Repeated_Path_MAX = Repeated_Path;
						Circle_6_cnt[Repeated_Path - 1]++;
					}
				}
			}
		}
		M_Example_Row[i] = ZEORS;
	}

	long result_Circle_6 = 0;
	for (int sum_cnt = 0; sum_cnt < int(Circle_6_cnt.size()); sum_cnt++) {
		if (Circle_6_cnt[sum_cnt] == 0)
			continue;
		result_Circle_6 += (Circle_6_cnt[sum_cnt] / (sum_cnt + 1));
	}
	return result_Circle_6;
}

//搜索名字为8个的祭品数量
int Fourier_8(
	vector<vector<short int>> & M_Example,
	vector<vector<short int>> & M_Example_Row,
	vector<vector<short int>> & M_Example_Column,
	short int& M_Example_Row_CNT_MAX,
	short int& M_Example_Column_CNT_MAX,
	short int& ROW, short int& COLUMN) {

	int SEQUENCE_MAX = M_Example_Row_CNT_MAX * M_Example_Row_CNT_MAX
		* M_Example_Column_CNT_MAX * M_Example_Column_CNT_MAX;

	vector<vector<short int>> Sequence(SEQUENCE_MAX, vector<short int>(4, 0));
	vector<vector<short int>> Sequence_Row(2, vector<short int>(3, 0));
	vector<vector<short int>> Sequence_Column(2, vector<short int>(4, 0));

	vector<short int>ZEORS(M_Example_Row_CNT_MAX, 0);
	int Repeated_Path_MAX = 0;
	vector<long>Circle_8_cnt(288, 0);

	for (int i = 0; i < ROW; i++) {

		int SEQUENCE_COUNT = 0;
		vector<int>NUMBER_SEQUENCE_PATH4(ROW, 0);

		for (int j = 0; j < M_Example_Row_CNT_MAX; j++) {
			short int Path1 = M_Example_Row[i][j];
			if (Path1 == 0)
				continue;
			for (int k = 0; k < M_Example_Column_CNT_MAX; k++) {
				short int Path2 = M_Example_Column[Path1 - 1][k];
				if (Path2 == 0 || Path2 == (i + 1))
					continue;
				for (int m = 0; m < M_Example_Row_CNT_MAX; m++) {
					short int Path3 = M_Example_Row[Path2 - 1][m];
					if (Path3 == 0 || Path3 == Path1)
						continue;
					for (int n = 0; n < M_Example_Column_CNT_MAX; n++) {
						short int Path4 = M_Example_Column[Path3 - 1][n];
						if (Path4 == 0 || Path4 == (i + 1) || Path4 == Path2)
							continue;
						if (M_Example_Row[Path4 - 1][0] == 0)
							continue;
						Sequence[SEQUENCE_COUNT] = { Path1,Path2,Path3,Path4 };
						SEQUENCE_COUNT++;
					}
				}
			}
		}



		for (int r = 0; r < SEQUENCE_COUNT; r++) {

			NUMBER_SEQUENCE_PATH4[Sequence[r][3] - 1]++;
		}

		int MAX_NUMBER_SEQUENCE_PATH4 = 0;

		for (int s = 0; s < ROW; s++) {
			if (NUMBER_SEQUENCE_PATH4[s] > MAX_NUMBER_SEQUENCE_PATH4)
				MAX_NUMBER_SEQUENCE_PATH4 = NUMBER_SEQUENCE_PATH4[s];
		}

		vector < vector<vector<short int>>>SEQUENCE_PATH4(ROW, vector < vector<short int>>(MAX_NUMBER_SEQUENCE_PATH4, vector<short int>(4, 0)));
		vector<int>NUMBER_SEQUENCE_PATH4_COUNT(ROW, 0);

		for (int t = 0; t < SEQUENCE_COUNT; t++) {
			SEQUENCE_PATH4[Sequence[t][3] - 1][NUMBER_SEQUENCE_PATH4_COUNT[Sequence[t][3] - 1]] = Sequence[t];
			NUMBER_SEQUENCE_PATH4_COUNT[Sequence[t][3] - 1]++;
		}

		for (int u = 0; u < ROW; u++) {
			if (NUMBER_SEQUENCE_PATH4[u] > 1) {
				for (int v = 0; v < NUMBER_SEQUENCE_PATH4[u]; v++) {
					for (int w = v + 1; w < NUMBER_SEQUENCE_PATH4[u]; w++) {
						if (SEQUENCE_PATH4[u][w][0] == SEQUENCE_PATH4[u][v][0] || SEQUENCE_PATH4[u][w][0] == SEQUENCE_PATH4[u][v][2])
							continue;
						if (SEQUENCE_PATH4[u][w][1] == SEQUENCE_PATH4[u][v][1])
							continue;
						if (SEQUENCE_PATH4[u][w][2] == SEQUENCE_PATH4[u][v][0] || SEQUENCE_PATH4[u][w][2] == SEQUENCE_PATH4[u][v][2])
							continue;

						int Repeated_Path = 0;
						Sequence_Row[0] = { SEQUENCE_PATH4[u][w][1],SEQUENCE_PATH4[u][v][1],SEQUENCE_PATH4[u][w][3] };
						Sequence_Column[0] = { SEQUENCE_PATH4[u][w][0],SEQUENCE_PATH4[u][v][0],SEQUENCE_PATH4[u][w][2] ,SEQUENCE_PATH4[u][v][2] };

						for (int Repeated_e = 0; Repeated_e < 4; Repeated_e++) {
							Sequence_Row[1] = { 1,1,1 };
							Sequence_Column[1] = { 1,1,1,1 };
							if (M_Example[i][Sequence_Column[0][Repeated_e] - 1] == 1) {
								Sequence_Column[1][Repeated_e] = 0;
								for (int Repeated_f = 0; Repeated_f < 4; Repeated_f++) {
									if (Sequence_Column[1][Repeated_f] == 0)
										continue;
									if (M_Example[i][Sequence_Column[0][Repeated_f] - 1] == 1) {
										Sequence_Column[1][Repeated_f] = 0;
										for (int Repeated_i = 0; Repeated_i < 3; Repeated_i++) {
											if (M_Example[Sequence_Row[0][Repeated_i] - 1][Sequence_Column[0][Repeated_e] - 1] == 1) {
												Sequence_Row[1][Repeated_i] = 0;
												for (int Repeated_j = 0; Repeated_j < 3; Repeated_j++) {
													if (Sequence_Row[1][Repeated_j] == 0)
														continue;
													if (M_Example[Sequence_Row[0][Repeated_j] - 1][Sequence_Column[0][Repeated_f] - 1] == 1) {
														Sequence_Row[1][Repeated_j] = 0;
														for (int Repeated_k = 0; Repeated_k < 4; Repeated_k++) {
															if (Sequence_Column[1][Repeated_k] == 0)
																continue;
															if (M_Example[Sequence_Row[0][Repeated_i] - 1][Sequence_Column[0][Repeated_k] - 1] == 1) {
																Sequence_Column[1][Repeated_k] = 0;
																for (int Repeated_m = 0; Repeated_m < 4; Repeated_m++) {
																	if (Sequence_Column[1][Repeated_m] == 0)
																		continue;
																	if (M_Example[Sequence_Row[0][Repeated_j] - 1][Sequence_Column[0][Repeated_m] - 1] == 1) {
																		Sequence_Column[1][Repeated_m] = 0;
																		for (int Repeated_n = 0; Repeated_n < 3; Repeated_n++) {
																			if (Sequence_Row[1][Repeated_n] == 0)
																				continue;
																			if (M_Example[Sequence_Row[0][Repeated_n] - 1][Sequence_Column[0][Repeated_k] - 1] == 1 && M_Example[Sequence_Row[0][Repeated_n] - 1][Sequence_Column[0][Repeated_m] - 1] == 1) {
																				Sequence_Row[1][Repeated_n] = 0;
																				Repeated_Path++;
																			}
																			Sequence_Row[1][Repeated_n] = 1;
																		}
																	}
																	Sequence_Column[1][Repeated_m] = 1;
																}
															}
															Sequence_Column[1][Repeated_k] = 1;
														}
													}
													Sequence_Row[1][Repeated_j] = 1;
												}
											}
											Sequence_Row[1][Repeated_i] = 1;
										}
									}
									Sequence_Column[1][Repeated_f] = 1;
								}
							}
							Sequence_Column[1][Repeated_e] = 1;
						}
						if ((int(Repeated_Path) % 2) != 0)
							cout << "Repeated_Path Error:" << Repeated_Path << endl;
						else
							Repeated_Path = Repeated_Path / 2;
						if (Repeated_Path > Repeated_Path_MAX)
							Repeated_Path_MAX = Repeated_Path;
						Circle_8_cnt[Repeated_Path - 1]++;
					}
				}
			}
		}
		M_Example_Row[i] = ZEORS;
	}
	long result_Circle_8 = 0;
	for (int sum_cnt = 0; sum_cnt < int(Circle_8_cnt.size()); sum_cnt++) {
		if (Circle_8_cnt[sum_cnt] == 0)
			continue;
		result_Circle_8 += (Circle_8_cnt[sum_cnt] / (sum_cnt + 1));
	}

	return result_Circle_8;
}

//搜索名字为10个的祭品数量
int Fourier_10(
	vector<vector<short int>> & M_Example,
	vector<vector<short int>> & M_Example_Row,
	vector<vector<short int>> & M_Example_Column,
	short int& M_Example_Row_CNT_MAX,
	short int& M_Example_Column_CNT_MAX,
	short int& ROW, short int& COLUMN) {


	int SEQUENCE_MAX = M_Example_Row_CNT_MAX * M_Example_Row_CNT_MAX * M_Example_Row_CNT_MAX
		* M_Example_Column_CNT_MAX * M_Example_Column_CNT_MAX;

	vector<vector<short int>> Sequence(SEQUENCE_MAX, vector<short int>(5, 0));
	vector<vector<short int>> Sequence_Row(2, vector<short int>(4, 0));
	vector<vector<short int>> Sequence_Column(2, vector<short int>(5, 0));

	vector<short int>ZEORS(M_Example_Row_CNT_MAX, 0);
	int Repeated_Path_MAX = 0;
	vector<long>Circle_10_cnt(1024, 0);

	for (int i = 0; i < ROW; i++) {

		int SEQUENCE_COUNT = 0;
		vector<int>NUMBER_SEQUENCE_PATH5(COLUMN, 0);


		for (int j = 0; j < M_Example_Row_CNT_MAX; j++) {
			short int Path1 = M_Example_Row[i][j];
			if (Path1 == 0)
				continue;
			for (int k = 0; k < M_Example_Column_CNT_MAX; k++) {
				short int Path2 = M_Example_Column[Path1 - 1][k];
				if (Path2 == 0 || Path2 == (i + 1))
					continue;
				for (int m = 0; m < M_Example_Row_CNT_MAX; m++) {
					short int Path3 = M_Example_Row[Path2 - 1][m];
					if (Path3 == 0 || Path3 == Path1)
						continue;
					for (int n = 0; n < M_Example_Column_CNT_MAX; n++) {
						short int Path4 = M_Example_Column[Path3 - 1][n];
						if (Path4 == 0 || Path4 == (i + 1) || Path4 == Path2)
							continue;
						for (int p = 0; p < M_Example_Row_CNT_MAX; p++) {
							short int Path5 = M_Example_Row[Path4 - 1][p];
							if (Path5 == 0 || Path5 == Path1 || Path5 == Path3)
								continue;
							Sequence[SEQUENCE_COUNT] = { Path1,Path2,Path3,Path4,Path5 };
							SEQUENCE_COUNT++;
						}
					}
				}
			}
		}



		for (int r = 0; r < SEQUENCE_COUNT; r++) {
			NUMBER_SEQUENCE_PATH5[Sequence[r][4] - 1]++;
		}

		int MAX_NUMBER_SEQUENCE_PATH5 = 0;

		for (int s = 0; s < COLUMN; s++) {
			if (NUMBER_SEQUENCE_PATH5[s] > MAX_NUMBER_SEQUENCE_PATH5)
				MAX_NUMBER_SEQUENCE_PATH5 = NUMBER_SEQUENCE_PATH5[s];
		}

		vector < vector<vector<short int>>>SEQUENCE_PATH5(COLUMN, vector < vector<short int>>(MAX_NUMBER_SEQUENCE_PATH5, vector<short int>(5, 0)));
		vector<int>NUMBER_SEQUENCE_PATH5_COUNT(COLUMN, 0);

		for (int t = 0; t < SEQUENCE_COUNT; t++) {
			SEQUENCE_PATH5[Sequence[t][4] - 1][NUMBER_SEQUENCE_PATH5_COUNT[Sequence[t][4] - 1]] = Sequence[t];
			NUMBER_SEQUENCE_PATH5_COUNT[Sequence[t][4] - 1]++;
		}

		for (int u = 0; u < COLUMN; u++) {
			if (NUMBER_SEQUENCE_PATH5[u] > 1) {
				for (int v = 0; v < NUMBER_SEQUENCE_PATH5[u]; v++) {
					for (int w = v + 1; w < NUMBER_SEQUENCE_PATH5[u]; w++) {
						if (SEQUENCE_PATH5[u][w][0] == SEQUENCE_PATH5[u][v][0] || SEQUENCE_PATH5[u][w][0] == SEQUENCE_PATH5[u][v][2])
							continue;
						if (SEQUENCE_PATH5[u][w][1] == SEQUENCE_PATH5[u][v][1] || SEQUENCE_PATH5[u][w][1] == SEQUENCE_PATH5[u][v][3])
							continue;
						if (SEQUENCE_PATH5[u][w][2] == SEQUENCE_PATH5[u][v][0] || SEQUENCE_PATH5[u][w][2] == SEQUENCE_PATH5[u][v][2])
							continue;
						if (SEQUENCE_PATH5[u][w][3] == SEQUENCE_PATH5[u][v][1] || SEQUENCE_PATH5[u][w][3] == SEQUENCE_PATH5[u][v][3])
							continue;
						int Repeated_Path = 0;
						Sequence_Row[0] = { SEQUENCE_PATH5[u][w][1],SEQUENCE_PATH5[u][v][1],SEQUENCE_PATH5[u][w][3],SEQUENCE_PATH5[u][v][3] };
						Sequence_Column[0] = { SEQUENCE_PATH5[u][w][0],SEQUENCE_PATH5[u][v][0],SEQUENCE_PATH5[u][w][2] ,SEQUENCE_PATH5[u][v][2],SEQUENCE_PATH5[u][w][4] };

						for (int Repeated_e = 0; Repeated_e < 5; Repeated_e++) {
							Sequence_Row[1] = { 1,1,1,1 };
							Sequence_Column[1] = { 1,1,1,1,1 };
							if (M_Example[i][Sequence_Column[0][Repeated_e] - 1] == 1) {
								Sequence_Column[1][Repeated_e] = 0;
								for (int Repeated_f = 0; Repeated_f < 5; Repeated_f++) {
									if (Sequence_Column[1][Repeated_f] == 0)
										continue;
									if (M_Example[i][Sequence_Column[0][Repeated_f] - 1] == 1) {
										Sequence_Column[1][Repeated_f] = 0;
										for (int Repeated_i = 0; Repeated_i < 4; Repeated_i++) {
											if (M_Example[Sequence_Row[0][Repeated_i] - 1][Sequence_Column[0][Repeated_e] - 1] == 1) {
												Sequence_Row[1][Repeated_i] = 0;
												for (int Repeated_j = 0; Repeated_j < 4; Repeated_j++) {
													if (Sequence_Row[1][Repeated_j] == 0)
														continue;
													if (M_Example[Sequence_Row[0][Repeated_j] - 1][Sequence_Column[0][Repeated_f] - 1] == 1) {
														Sequence_Row[1][Repeated_j] = 0;
														for (int Repeated_k = 0; Repeated_k < 5; Repeated_k++) {
															if (Sequence_Column[1][Repeated_k] == 0)
																continue;
															if (M_Example[Sequence_Row[0][Repeated_i] - 1][Sequence_Column[0][Repeated_k] - 1] == 1) {
																Sequence_Column[1][Repeated_k] = 0;
																for (int Repeated_m = 0; Repeated_m < 5; Repeated_m++) {
																	if (Sequence_Column[1][Repeated_m] == 0)
																		continue;
																	if (M_Example[Sequence_Row[0][Repeated_j] - 1][Sequence_Column[0][Repeated_m] - 1] == 1) {
																		Sequence_Column[1][Repeated_m] = 0;
																		for (int Repeated_n = 0; Repeated_n < 4; Repeated_n++) {
																			if (Sequence_Row[1][Repeated_n] == 0)
																				continue;
																			if (M_Example[Sequence_Row[0][Repeated_n] - 1][Sequence_Column[0][Repeated_k] - 1] == 1) {
																				Sequence_Row[1][Repeated_n] = 0;
																				for (int Repeated_p = 0; Repeated_p < 4; Repeated_p++) {
																					if (Sequence_Row[1][Repeated_p] == 0)
																						continue;
																					if (M_Example[Sequence_Row[0][Repeated_p] - 1][Sequence_Column[0][Repeated_m] - 1] == 1) {
																						Sequence_Row[1][Repeated_p] = 0;
																						for (int Repeated_q = 0; Repeated_q < 5; Repeated_q++) {
																							if (Sequence_Column[1][Repeated_q] == 0)
																								continue;
																							if (M_Example[Sequence_Row[0][Repeated_n] - 1][Sequence_Column[0][Repeated_q] - 1] == 1 && M_Example[Sequence_Row[0][Repeated_p] - 1][Sequence_Column[0][Repeated_q] - 1] == 1) {
																								Sequence_Column[1][Repeated_q] = 0;
																								Repeated_Path++;
																							}
																							Sequence_Column[1][Repeated_q] = 1;
																						}
																					}
																					Sequence_Row[1][Repeated_p] = 1;
																				}
																			}
																			Sequence_Row[1][Repeated_n] = 1;
																		}
																	}
																	Sequence_Column[1][Repeated_m] = 1;
																}
															}
															Sequence_Column[1][Repeated_k] = 1;
														}
													}
													Sequence_Row[1][Repeated_j] = 1;
												}
											}
											Sequence_Row[1][Repeated_i] = 1;
										}
									}
									Sequence_Column[1][Repeated_f] = 1;
								}
							}
							Sequence_Column[1][Repeated_e] = 1;
						}
						if ((int(Repeated_Path) % 2) != 0)
							cout << "Repeated_Path Error:" << Repeated_Path << endl;
						else
							Repeated_Path = Repeated_Path / 2;
						if (Repeated_Path > Repeated_Path_MAX)
							Repeated_Path_MAX = Repeated_Path;
						Circle_10_cnt[Repeated_Path - 1]++;
					}
				}
			}
		}
		M_Example_Row[i] = ZEORS;
	}


	long result_Circle_10 = 0;
	for (int sum_cnt = 0; sum_cnt < int(Circle_10_cnt.size()); sum_cnt++) {
		if (Circle_10_cnt[sum_cnt] == 0)
			continue;
		result_Circle_10 += (Circle_10_cnt[sum_cnt] / (sum_cnt + 1));
	}
	return result_Circle_10;
}

//搜索名字为12个的祭品数量
int Fourier_12(
	vector<vector<short int>> & M_Example,
	vector<vector<short int>> & M_Example_Row,
	vector<vector<short int>> & M_Example_Column,
	short int& M_Example_Row_CNT_MAX,
	short int& M_Example_Column_CNT_MAX,
	short int& ROW, short int& COLUMN) {


	int SEQUENCE_MAX = M_Example_Row_CNT_MAX * M_Example_Row_CNT_MAX * M_Example_Row_CNT_MAX
		* M_Example_Column_CNT_MAX * M_Example_Column_CNT_MAX * M_Example_Column_CNT_MAX;

	vector<vector<short int>> Sequence(SEQUENCE_MAX, vector<short int>(6, 0));
	vector<vector<short int>> Sequence_Row(2, vector<short int>(5, 0));
	vector<vector<short int>> Sequence_Column(2, vector<short int>(6, 0));

	vector<int>Circle_12_Suspected(ROW, 0);
	vector<short int>ZEORS(M_Example_Row_CNT_MAX, 0);
	int Repeated_Path_MAX = 0;
	vector<long>Circle_12_cnt(4096, 0);

	for (int i = 0; i < ROW; i++) {

		int SEQUENCE_COUNT = 0;
		int Circle_12_Suspected_cnt = 0;
		vector<int>NUMBER_SEQUENCE_PATH6(ROW, 0);

		for (int j = 0; j < M_Example_Row_CNT_MAX; j++) {
			short int Path1 = M_Example_Row[i][j];
			if (Path1 == 0)
				continue;
			for (int k = 0; k < M_Example_Column_CNT_MAX; k++) {
				short int Path2 = M_Example_Column[Path1 - 1][k];
				if (Path2 == 0 || Path2 == (i + 1))
					continue;
				for (int m = 0; m < M_Example_Row_CNT_MAX; m++) {
					short int Path3 = M_Example_Row[Path2 - 1][m];
					if (Path3 == 0 || Path3 == Path1)
						continue;
					for (int n = 0; n < M_Example_Column_CNT_MAX; n++) {
						short int Path4 = M_Example_Column[Path3 - 1][n];
						if (Path4 == 0 || Path4 == (i + 1) || Path4 == Path2)
							continue;
						for (int p = 0; p < M_Example_Row_CNT_MAX; p++) {
							short int Path5 = M_Example_Row[Path4 - 1][p];
							if (Path5 == 0 || Path5 == Path1 || Path5 == Path3)
								continue;
							for (int q = 0; q < M_Example_Column_CNT_MAX; q++) {
								short int Path6 = M_Example_Column[Path5 - 1][q];
								if (Path6 == 0 || Path6 == (i + 1) || Path6 == Path2 || Path6 == Path4)
									continue;
								if (M_Example_Row[Path6 - 1][0] == 0)
									continue;
								Sequence[SEQUENCE_COUNT] = { Path1,Path2,Path3,Path4,Path5,Path6 };
								SEQUENCE_COUNT++;
							}
						}
					}
				}
			}
		}



		for (int r = 0; r < SEQUENCE_COUNT; r++) {
			NUMBER_SEQUENCE_PATH6[Sequence[r][5] - 1]++;
		}

		int MAX_NUMBER_SEQUENCE_PATH6 = 0;

		for (int s = 0; s < ROW; s++) {
			if (NUMBER_SEQUENCE_PATH6[s] > MAX_NUMBER_SEQUENCE_PATH6)
				MAX_NUMBER_SEQUENCE_PATH6 = NUMBER_SEQUENCE_PATH6[s];
		}

		vector < vector<vector<short int>>>SEQUENCE_PATH6(ROW, vector < vector<short int>>(MAX_NUMBER_SEQUENCE_PATH6, vector<short int>(6, 0)));
		vector<int>NUMBER_SEQUENCE_PATH6_COUNT(ROW, 0);

		for (int t = 0; t < SEQUENCE_COUNT; t++) {
			SEQUENCE_PATH6[Sequence[t][5] - 1][NUMBER_SEQUENCE_PATH6_COUNT[Sequence[t][5] - 1]] = Sequence[t];
			NUMBER_SEQUENCE_PATH6_COUNT[Sequence[t][5] - 1]++;
		}

		for (int u = 0; u < ROW; u++) {
			if (NUMBER_SEQUENCE_PATH6[u] > 1) {
				for (int v = 0; v < NUMBER_SEQUENCE_PATH6[u]; v++) {
					for (int w = v + 1; w < NUMBER_SEQUENCE_PATH6[u]; w++) {
						if (SEQUENCE_PATH6[u][w][0] == SEQUENCE_PATH6[u][v][0] || SEQUENCE_PATH6[u][w][0] == SEQUENCE_PATH6[u][v][2] || SEQUENCE_PATH6[u][w][0] == SEQUENCE_PATH6[u][v][4])
							continue;
						if (SEQUENCE_PATH6[u][w][1] == SEQUENCE_PATH6[u][v][1] || SEQUENCE_PATH6[u][w][1] == SEQUENCE_PATH6[u][v][3])
							continue;
						if (SEQUENCE_PATH6[u][w][2] == SEQUENCE_PATH6[u][v][0] || SEQUENCE_PATH6[u][w][2] == SEQUENCE_PATH6[u][v][2] || SEQUENCE_PATH6[u][w][2] == SEQUENCE_PATH6[u][v][4])
							continue;
						if (SEQUENCE_PATH6[u][w][3] == SEQUENCE_PATH6[u][v][1] || SEQUENCE_PATH6[u][w][3] == SEQUENCE_PATH6[u][v][3])
							continue;
						if (SEQUENCE_PATH6[u][w][4] == SEQUENCE_PATH6[u][v][0] || SEQUENCE_PATH6[u][w][4] == SEQUENCE_PATH6[u][v][2] || SEQUENCE_PATH6[u][w][4] == SEQUENCE_PATH6[u][v][4])
							continue;
						Circle_12_Suspected_cnt++;
						int Repeated_Path = 0;
						Sequence_Row[0] = { SEQUENCE_PATH6[u][w][1],SEQUENCE_PATH6[u][v][1],SEQUENCE_PATH6[u][w][3],SEQUENCE_PATH6[u][v][3],SEQUENCE_PATH6[u][w][5] };
						Sequence_Column[0] = { SEQUENCE_PATH6[u][w][0],SEQUENCE_PATH6[u][v][0],SEQUENCE_PATH6[u][w][2] ,SEQUENCE_PATH6[u][v][2],SEQUENCE_PATH6[u][w][4],SEQUENCE_PATH6[u][v][4] };
						for (int Repeated_e = 0; Repeated_e < 6; Repeated_e++) {
							Sequence_Row[1] = { 1,1,1,1,1 };
							Sequence_Column[1] = { 1,1,1,1,1,1 };
							if (M_Example[i][Sequence_Column[0][Repeated_e] - 1] == 1) {
								Sequence_Column[1][Repeated_e] = 0;
								for (int Repeated_f = 0; Repeated_f < 6; Repeated_f++) {
									if (Sequence_Column[1][Repeated_f] == 0)
										continue;
									if (M_Example[i][Sequence_Column[0][Repeated_f] - 1] == 1) {
										Sequence_Column[1][Repeated_f] = 0;
										for (int Repeated_i = 0; Repeated_i < 5; Repeated_i++) {
											if (M_Example[Sequence_Row[0][Repeated_i] - 1][Sequence_Column[0][Repeated_e] - 1] == 1) {
												Sequence_Row[1][Repeated_i] = 0;
												for (int Repeated_j = 0; Repeated_j < 5; Repeated_j++) {
													if (Sequence_Row[1][Repeated_j] == 0)
														continue;
													if (M_Example[Sequence_Row[0][Repeated_j] - 1][Sequence_Column[0][Repeated_f] - 1] == 1) {
														Sequence_Row[1][Repeated_j] = 0;
														for (int Repeated_k = 0; Repeated_k < 6; Repeated_k++) {
															if (Sequence_Column[1][Repeated_k] == 0)
																continue;
															if (M_Example[Sequence_Row[0][Repeated_i] - 1][Sequence_Column[0][Repeated_k] - 1] == 1) {
																Sequence_Column[1][Repeated_k] = 0;
																for (int Repeated_m = 0; Repeated_m < 6; Repeated_m++) {
																	if (Sequence_Column[1][Repeated_m] == 0)
																		continue;
																	if (M_Example[Sequence_Row[0][Repeated_j] - 1][Sequence_Column[0][Repeated_m] - 1] == 1) {
																		Sequence_Column[1][Repeated_m] = 0;
																		for (int Repeated_n = 0; Repeated_n < 5; Repeated_n++) {
																			if (Sequence_Row[1][Repeated_n] == 0)
																				continue;
																			if (M_Example[Sequence_Row[0][Repeated_n] - 1][Sequence_Column[0][Repeated_k] - 1] == 1) {
																				Sequence_Row[1][Repeated_n] = 0;
																				for (int Repeated_p = 0; Repeated_p < 5; Repeated_p++) {
																					if (Sequence_Row[1][Repeated_p] == 0)
																						continue;
																					if (M_Example[Sequence_Row[0][Repeated_p] - 1][Sequence_Column[0][Repeated_m] - 1] == 1) {
																						Sequence_Row[1][Repeated_p] = 0;
																						for (int Repeated_q = 0; Repeated_q < 6; Repeated_q++) {
																							if (Sequence_Column[1][Repeated_q] == 0)
																								continue;
																							if (M_Example[Sequence_Row[0][Repeated_n] - 1][Sequence_Column[0][Repeated_q] - 1] == 1) {
																								Sequence_Column[1][Repeated_q] = 0;
																								for (int Repeated_r = 0; Repeated_r < 6; Repeated_r++) {
																									if (Sequence_Column[1][Repeated_r] == 0)
																										continue;
																									if (M_Example[Sequence_Row[0][Repeated_p] - 1][Sequence_Column[0][Repeated_r] - 1] == 1) {
																										Sequence_Column[1][Repeated_r] = 0;
																										for (int Repeated_s = 0; Repeated_s < 5; Repeated_s++) {
																											if (Sequence_Row[1][Repeated_s] == 0)
																												continue;
																											if (M_Example[Sequence_Row[0][Repeated_s] - 1][Sequence_Column[0][Repeated_q] - 1] == 1 && M_Example[Sequence_Row[0][Repeated_s] - 1][Sequence_Column[0][Repeated_r] - 1] == 1) {
																												Sequence_Row[1][Repeated_s] = 0;
																												Repeated_Path++;
																											}
																											Sequence_Row[1][Repeated_s] = 1;
																										}
																									}
																									Sequence_Column[1][Repeated_r] = 1;
																								}
																							}
																							Sequence_Column[1][Repeated_q] = 1;
																						}
																					}
																					Sequence_Row[1][Repeated_p] = 1;
																				}
																			}
																			Sequence_Row[1][Repeated_n] = 1;
																		}
																	}
																	Sequence_Column[1][Repeated_m] = 1;
																}
															}
															Sequence_Column[1][Repeated_k] = 1;
														}
													}
													Sequence_Row[1][Repeated_j] = 1;
												}
											}
											Sequence_Row[1][Repeated_i] = 1;
										}
									}
									Sequence_Column[1][Repeated_f] = 1;
								}
							}
							Sequence_Column[1][Repeated_e] = 1;
						}
						if ((int(Repeated_Path) % 2) != 0)
							cout << "Repeated_Path Error:" << Repeated_Path << endl;
						else
							Repeated_Path = Repeated_Path / 2;
						if (Repeated_Path > Repeated_Path_MAX)
							Repeated_Path_MAX = Repeated_Path;
						Circle_12_cnt[Repeated_Path - 1]++;
					}
				}
			}
		}
		M_Example_Row[i] = ZEORS;
	}


	long result_Circle_12 = 0;
	for (int sum_cnt = 0; sum_cnt < int(Circle_12_cnt.size()); sum_cnt++) {
		if (Circle_12_cnt[sum_cnt] == 0)
			continue;
		result_Circle_12 += (Circle_12_cnt[sum_cnt] / (sum_cnt + 1));
	}
	return result_Circle_12;
}

//搜索名字为14个的祭品数量
int Fourier_14(
	vector<vector<short int>> & M_Example,
	vector<vector<short int>> & M_Example_Row,
	vector<vector<short int>> & M_Example_Column,
	short int& M_Example_Row_CNT_MAX,
	short int& M_Example_Column_CNT_MAX,
	short int& ROW, short int& COLUMN) {


	int SEQUENCE_MAX = M_Example_Row_CNT_MAX * M_Example_Row_CNT_MAX * M_Example_Row_CNT_MAX * M_Example_Row_CNT_MAX
		* M_Example_Column_CNT_MAX * M_Example_Column_CNT_MAX * M_Example_Column_CNT_MAX;

	vector<vector<short int>> Sequence(SEQUENCE_MAX, vector<short int>(7, 0));
	vector<vector<short int>> Sequence_Row(2, vector<short int>(6, 0));
	vector<vector<short int>> Sequence_Column(2, vector<short int>(7, 0));

	vector<short int>ZEORS(COLUMN, 0);
	int Repeated_Path_MAX = 0;
	vector<long>Circle_14_cnt(8192, 0);

	for (int i = 0; i < ROW; i++) {

		int SEQUENCE_COUNT = 0;
		vector<int>NUMBER_SEQUENCE_PATH7(COLUMN, 0);

		for (int j = 0; j < M_Example_Row_CNT_MAX; j++) {
			short int Path1 = M_Example_Row[i][j];
			if (Path1 == 0)
				continue;
			for (int k = 0; k < M_Example_Column_CNT_MAX; k++) {
				short int Path2 = M_Example_Column[Path1 - 1][k];
				if (Path2 == 0 || Path2 == (i + 1))
					continue;
				for (int m = 0; m < M_Example_Row_CNT_MAX; m++) {
					short int Path3 = M_Example_Row[Path2 - 1][m];
					if (Path3 == 0 || Path3 == Path1)
						continue;
					for (int n = 0; n < M_Example_Column_CNT_MAX; n++) {
						short int Path4 = M_Example_Column[Path3 - 1][n];
						if (Path4 == 0 || Path4 == (i + 1) || Path4 == Path2)
							continue;
						for (int p = 0; p < M_Example_Row_CNT_MAX; p++) {
							short int Path5 = M_Example_Row[Path4 - 1][p];
							if (Path5 == 0 || Path5 == Path1 || Path5 == Path3)
								continue;
							for (int q = 0; q < M_Example_Column_CNT_MAX; q++) {
								short int Path6 = M_Example_Column[Path5 - 1][q];
								if (Path6 == 0 || Path6 == (i + 1) || Path6 == Path2 || Path6 == Path4)
									continue;
								for (int r = 0; r < M_Example_Row_CNT_MAX; r++) {
									short int Path7 = M_Example_Row[Path6 - 1][r];
									if (Path7 == 0 || Path7 == Path1 || Path7 == Path3 || Path7 == Path5)
										continue;
									Sequence[SEQUENCE_COUNT] = { Path1,Path2,Path3,Path4,Path5,Path6,Path7 };
									SEQUENCE_COUNT++;
								}
							}
						}
					}
				}
			}
		}
		for (int s = 0; s < SEQUENCE_COUNT; s++) {
			NUMBER_SEQUENCE_PATH7[Sequence[s][6] - 1]++;
		}

		int MAX_NUMBER_SEQUENCE_PATH7 = 0;

		for (int t = 0; t < COLUMN; t++) {
			if (NUMBER_SEQUENCE_PATH7[t] > MAX_NUMBER_SEQUENCE_PATH7)
				MAX_NUMBER_SEQUENCE_PATH7 = NUMBER_SEQUENCE_PATH7[t];
		}

		vector < vector<vector<short int>>>SEQUENCE_PATH7(COLUMN, vector < vector<short int>>(MAX_NUMBER_SEQUENCE_PATH7, vector<short int>(7, 0)));
		vector<int>NUMBER_SEQUENCE_PATH7_COUNT(COLUMN, 0);

		for (int u = 0; u < SEQUENCE_COUNT; u++) {
			SEQUENCE_PATH7[Sequence[u][6] - 1][NUMBER_SEQUENCE_PATH7_COUNT[Sequence[u][6] - 1]] = Sequence[u];
			NUMBER_SEQUENCE_PATH7_COUNT[Sequence[u][6] - 1]++;
		}

		for (int v = 0; v < COLUMN; v++) {
			if (NUMBER_SEQUENCE_PATH7[v] > 1) {
				for (int w = 0; w < NUMBER_SEQUENCE_PATH7[v]; w++) {
					for (int x = w + 1; x < NUMBER_SEQUENCE_PATH7[v]; x++) {
						if (SEQUENCE_PATH7[v][x][0] == SEQUENCE_PATH7[v][w][0] || SEQUENCE_PATH7[v][x][0] == SEQUENCE_PATH7[v][w][2] || SEQUENCE_PATH7[v][x][0] == SEQUENCE_PATH7[v][w][4])
							continue;
						if (SEQUENCE_PATH7[v][x][1] == SEQUENCE_PATH7[v][w][1] || SEQUENCE_PATH7[v][x][1] == SEQUENCE_PATH7[v][w][3] || SEQUENCE_PATH7[v][x][1] == SEQUENCE_PATH7[v][w][5])
							continue;
						if (SEQUENCE_PATH7[v][x][2] == SEQUENCE_PATH7[v][w][0] || SEQUENCE_PATH7[v][x][2] == SEQUENCE_PATH7[v][w][2] || SEQUENCE_PATH7[v][x][2] == SEQUENCE_PATH7[v][w][4])
							continue;
						if (SEQUENCE_PATH7[v][x][3] == SEQUENCE_PATH7[v][w][1] || SEQUENCE_PATH7[v][x][3] == SEQUENCE_PATH7[v][w][3] || SEQUENCE_PATH7[v][x][3] == SEQUENCE_PATH7[v][w][5])
							continue;
						if (SEQUENCE_PATH7[v][x][4] == SEQUENCE_PATH7[v][w][0] || SEQUENCE_PATH7[v][x][4] == SEQUENCE_PATH7[v][w][2] || SEQUENCE_PATH7[v][x][4] == SEQUENCE_PATH7[v][w][4])
							continue;
						if (SEQUENCE_PATH7[v][x][5] == SEQUENCE_PATH7[v][w][1] || SEQUENCE_PATH7[v][x][5] == SEQUENCE_PATH7[v][w][3] || SEQUENCE_PATH7[v][x][5] == SEQUENCE_PATH7[v][w][5])
							continue;

						int Repeated_Path = 0;

						Sequence_Row[0] = { SEQUENCE_PATH7[v][w][1] ,SEQUENCE_PATH7[v][x][1],SEQUENCE_PATH7[v][w][3] ,SEQUENCE_PATH7[v][x][3],SEQUENCE_PATH7[v][w][5] ,SEQUENCE_PATH7[v][x][5] };
						Sequence_Column[0] = { SEQUENCE_PATH7[v][w][0],SEQUENCE_PATH7[v][x][0],SEQUENCE_PATH7[v][w][2],SEQUENCE_PATH7[v][x][2],SEQUENCE_PATH7[v][w][4],SEQUENCE_PATH7[v][x][4],SEQUENCE_PATH7[v][w][6] };
						for (int Repeated_e = 0; Repeated_e < 7; Repeated_e++) {
							Sequence_Row[1] = { 1,1,1,1,1,1 };
							Sequence_Column[1] = { 1,1,1,1,1,1,1 };
							if (M_Example[i][Sequence_Column[0][Repeated_e] - 1] == 1) {
								Sequence_Column[1][Repeated_e] = 0;
								for (int Repeated_f = 0; Repeated_f < 7; Repeated_f++) {
									if (Sequence_Column[1][Repeated_f] == 0)
										continue;
									if (M_Example[i][Sequence_Column[0][Repeated_f] - 1] == 1) {
										Sequence_Column[1][Repeated_f] = 0;
										for (int Repeated_i = 0; Repeated_i < 6; Repeated_i++) {
											if (M_Example[Sequence_Row[0][Repeated_i] - 1][Sequence_Column[0][Repeated_e] - 1] == 1) {
												Sequence_Row[1][Repeated_i] = 0;
												for (int Repeated_j = 0; Repeated_j < 6; Repeated_j++) {
													if (Sequence_Row[1][Repeated_j] == 0)
														continue;
													if (M_Example[Sequence_Row[0][Repeated_j] - 1][Sequence_Column[0][Repeated_f] - 1] == 1) {
														Sequence_Row[1][Repeated_j] = 0;
														for (int Repeated_k = 0; Repeated_k < 7; Repeated_k++) {
															if (Sequence_Column[1][Repeated_k] == 0)
																continue;
															if (M_Example[Sequence_Row[0][Repeated_i] - 1][Sequence_Column[0][Repeated_k] - 1] == 1) {
																Sequence_Column[1][Repeated_k] = 0;
																for (int Repeated_m = 0; Repeated_m < 7; Repeated_m++) {
																	if (Sequence_Column[1][Repeated_m] == 0)
																		continue;
																	if (M_Example[Sequence_Row[0][Repeated_j] - 1][Sequence_Column[0][Repeated_m] - 1] == 1) {
																		Sequence_Column[1][Repeated_m] = 0;
																		for (int Repeated_n = 0; Repeated_n < 6; Repeated_n++) {
																			if (Sequence_Row[1][Repeated_n] == 0)
																				continue;
																			if (M_Example[Sequence_Row[0][Repeated_n] - 1][Sequence_Column[0][Repeated_k] - 1] == 1) {
																				Sequence_Row[1][Repeated_n] = 0;
																				for (int Repeated_p = 0; Repeated_p < 6; Repeated_p++) {
																					if (Sequence_Row[1][Repeated_p] == 0)
																						continue;
																					if (M_Example[Sequence_Row[0][Repeated_p] - 1][Sequence_Column[0][Repeated_m] - 1] == 1) {
																						Sequence_Row[1][Repeated_p] = 0;
																						for (int Repeated_q = 0; Repeated_q < 7; Repeated_q++) {
																							if (Sequence_Column[1][Repeated_q] == 0)
																								continue;
																							if (M_Example[Sequence_Row[0][Repeated_n] - 1][Sequence_Column[0][Repeated_q] - 1] == 1) {
																								Sequence_Column[1][Repeated_q] = 0;
																								for (int Repeated_r = 0; Repeated_r < 7; Repeated_r++) {
																									if (Sequence_Column[1][Repeated_r] == 0)
																										continue;
																									if (M_Example[Sequence_Row[0][Repeated_p] - 1][Sequence_Column[0][Repeated_r] - 1] == 1) {
																										Sequence_Column[1][Repeated_r] = 0;
																										for (int Repeated_s = 0; Repeated_s < 6; Repeated_s++) {
																											if (Sequence_Row[1][Repeated_s] == 0)
																												continue;
																											if (M_Example[Sequence_Row[0][Repeated_s] - 1][Sequence_Column[0][Repeated_q] - 1] == 1) {
																												Sequence_Row[1][Repeated_s] = 0;
																												for (int Repeated_t = 0; Repeated_t < 6; Repeated_t++) {
																													if (Sequence_Row[1][Repeated_t] == 0)
																														continue;
																													if (M_Example[Sequence_Row[0][Repeated_t] - 1][Sequence_Column[0][Repeated_r] - 1] == 1) {
																														Sequence_Row[1][Repeated_t] = 0;
																														for (int Repeated_u = 0; Repeated_u < 7; Repeated_u++) {
																															if (Sequence_Column[1][Repeated_u] == 0)
																																continue;
																															if (M_Example[Sequence_Row[0][Repeated_s] - 1][Sequence_Column[0][Repeated_u] - 1] == 1 && M_Example[Sequence_Row[0][Repeated_t] - 1][Sequence_Column[0][Repeated_u] - 1] == 1) {
																																Repeated_Path++;
																																Sequence_Column[1][Repeated_u] = 0;
																															}
																															Sequence_Column[1][Repeated_u] = 1;
																														}
																													}
																													Sequence_Row[1][Repeated_t] = 1;
																												}
																											}
																											Sequence_Row[1][Repeated_s] = 1;
																										}
																									}
																									Sequence_Column[1][Repeated_r] = 1;
																								}
																							}
																							Sequence_Column[1][Repeated_q] = 1;
																						}
																					}
																					Sequence_Row[1][Repeated_p] = 1;
																				}
																			}
																			Sequence_Row[1][Repeated_n] = 1;
																		}
																	}
																	Sequence_Column[1][Repeated_m] = 1;
																}
															}
															Sequence_Column[1][Repeated_k] = 1;
														}
													}
													Sequence_Row[1][Repeated_j] = 1;
												}
											}
											Sequence_Row[1][Repeated_i] = 1;
										}
									}
									Sequence_Column[1][Repeated_f] = 1;
								}
							}
							Sequence_Column[1][Repeated_e] = 1;
						}

						if ((int(Repeated_Path) % 2) != 0)
							cout << "Repeated_Path Error:" << Repeated_Path << endl;
						else
							Repeated_Path = Repeated_Path / 2;
						if (Repeated_Path > Repeated_Path_MAX)
							Repeated_Path_MAX = Repeated_Path;
						Circle_14_cnt[Repeated_Path - 1]++;
					}
				}
			}
		}
		M_Example_Row[i] = ZEORS;
	}

	long result_Circle_14 = 0;
	for (int sum_cnt = 0; sum_cnt < int(Circle_14_cnt.size()); sum_cnt++) {
		if (Circle_14_cnt[sum_cnt] == 0)
			continue;
		result_Circle_14 += (Circle_14_cnt[sum_cnt] / (sum_cnt + 1));
	}
	return result_Circle_14;
}

int main() {

	clock_t START_TIME, END_TIME;
	START_TIME = clock();

	vector<vector< short int> >M_Example;
	short int ROW = 0;
	short int COLUMN = 0;

	if (matrix_read(M_Example, ROW, COLUMN) != 0) {
		system("pause");
		return -1;
	}

	short int M_Example_Row_CNT_MAX = 0;
	short int M_Example_Column_CNT_MAX = 0;

	Adjacency_Matrix_R_C_Max(M_Example, M_Example_Row_CNT_MAX, M_Example_Column_CNT_MAX, ROW, COLUMN);


	vector<vector<short int>>M_Example_Row(ROW, vector<short int>(M_Example_Row_CNT_MAX));
	vector<vector<short int>>M_Example_Column(COLUMN, vector<short int>(M_Example_Column_CNT_MAX));


	Adjacency_Matrix_TO_Adjacency_Table(M_Example, M_Example_Row, M_Example_Column, ROW, COLUMN);

	vector<vector<short int>>M_Example_Row_TEMP(ROW, vector<short int>(M_Example_Row_CNT_MAX));

	M_Example_Row_TEMP.assign(M_Example_Row.begin(), M_Example_Row.end());

	long Result_4 = 0;
	long Result_6 = 0;
	long Result_8 = 0;
	long Result_10 = 0;
	long Result_12 = 0;
	long Result_14 = 0;


	Result_4 = Fourier_4(
		M_Example,
		M_Example_Row_TEMP,
		M_Example_Column,
		M_Example_Row_CNT_MAX,
		M_Example_Column_CNT_MAX,
		ROW, COLUMN
	);

	M_Example_Row_TEMP.assign(M_Example_Row.begin(), M_Example_Row.end());

	Result_6 = Fourier_6(
		M_Example,
		M_Example_Row_TEMP,
		M_Example_Column,
		M_Example_Row_CNT_MAX,
		M_Example_Column_CNT_MAX,
		ROW, COLUMN
	);

	M_Example_Row_TEMP.assign(M_Example_Row.begin(), M_Example_Row.end());

	Result_8 = Fourier_8(
		M_Example,
		M_Example_Row_TEMP,
		M_Example_Column,
		M_Example_Row_CNT_MAX,
		M_Example_Column_CNT_MAX,
		ROW, COLUMN
	);

	M_Example_Row_TEMP.assign(M_Example_Row.begin(), M_Example_Row.end());

	Result_10 = Fourier_10(
		M_Example,
		M_Example_Row_TEMP,
		M_Example_Column,
		M_Example_Row_CNT_MAX,
		M_Example_Column_CNT_MAX,
		ROW, COLUMN
	);

	M_Example_Row_TEMP.assign(M_Example_Row.begin(), M_Example_Row.end());

	Result_12 = Fourier_12(
		M_Example,
		M_Example_Row_TEMP,
		M_Example_Column,
		M_Example_Row_CNT_MAX,
		M_Example_Column_CNT_MAX,
		ROW, COLUMN
	);

	M_Example_Row_TEMP.assign(M_Example_Row.begin(), M_Example_Row.end());

	Result_14 = Fourier_14(
		M_Example,
		M_Example_Row_TEMP,
		M_Example_Column,
		M_Example_Row_CNT_MAX,
		M_Example_Column_CNT_MAX,
		ROW, COLUMN
	);

	ofstream out_file(OUTPUT_FILE_NAME);

	out_file << Result_4 << endl;
	out_file << Result_6 << endl;
	out_file << Result_8 << endl;
	out_file << Result_10 << endl;
	out_file << Result_12 << endl;
	out_file << Result_14 << endl;

	out_file.close();

	END_TIME = clock();

	double DELTA_TIME = double(double(END_TIME) - double(START_TIME)) / CLOCKS_PER_SEC;
	cout << "Run Time:" << DELTA_TIME << "s" << endl;

	system("pause");
	return 0;
}
