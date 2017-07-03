#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

char **input_file() {
	char **map, tmp, line[100];

	ifstream in("input.txt");
	map=(char **)malloc(sizeof(char *)*10);
	for(int i=0;i<10;i++) {
		map[i]=(char *)malloc(sizeof(char)*10);
	}
	in.getline(line, 100);
	in.getline(line, 100);

	for(int i=0;i<10;i++) {
		in.get();
		in.get();
		in.get();
		for(int j=0;;j++) {
			tmp=in.get();
			if(tmp=='\n') break;
			if(j%2!=0) continue;
			switch(tmp) {
				case 'A':
					map[i][j/2]='6';
					break;
				case 'B':
					map[i][j/2]='4';
					break;
				case 'S':
					map[i][j/2]='3';
					break;
				case 'D':
					map[i][j/2]='3';
					break;
				case 'P':
					map[i][j/2]='2';
					break;
				default:
					map[i][j/2]='0';
			}
		}
	}
	in.getline(line, 100);
	in.close();

	return map;
}

void find_6(char **bomb, int probability[][10]) {
	int ch;

	for(int i=0;i<11-6;i++) {
		for(int j=0;j<10;j++) {
			ch=0;
			for(int k=0;k<6;k++) {
				if(bomb[i+k][j]!=' ' && bomb[i+k][j]!='6') {
					ch=-1;
					break;
				}
			}
			if(ch!=-1) {
				for(int k=0;k<6;k++) {
					probability[i+k][j]++;
				}
			}
		}
	}
	for(int i=0;i<10;i++) {
		for(int j=0;j<11-6;j++) {
			ch=0;
			for(int k=0;k<6;k++) {
				if(bomb[i][j+k]!=' ' && bomb[i][j+k]!='6') {
					ch=-1;
					break;
				}
			}
			if(ch!=-1) {
				for(int k=0;k<6;k++) {
					probability[i][j+k]++;
				}
			}
		}
	}
}

void find_4(char **bomb, int probability[][10]) {
	int ch, check;

	for(int i=0;i<11-4;i++) {
		for(int j=0;j<10;j++) {
			ch=0;
			for(int m=0;m<4;m++) {
				if(bomb[i+m][j]!=' ' && bomb[i+m][j]!='4') {
					ch=-1;
					break;
				}
			}
			if(ch==-1) continue;
			for(int k=0;k<11-4;k++) {
				for(int l=0;l<10;l++) {
					if(i>k) break;
					if(i==k && j>l) continue;
					ch=0;
					for(int m=0;m<4;m++) {
						if(bomb[k+m][l]!=' ' && bomb[k+m][l]!='4') {
							ch=-1;
							break;
						}
					}
					if(ch!=-1) {
						check=0;
						for(int m=0;m<4;m++) {
							for(int n=0;n<4;n++) {
								if((i+m)==(k+n) && j==l) check=-1;
							}
							if(check==-1) break;
						}
						if(check!=-1) {
							for(int m=0;m<4;m++) {
								probability[i+m][j]++;
								probability[k+m][l]++;
							}
						}
					}
				}
			}
			for(int k=0;k<10;k++) {
				for(int l=0;l<11-4;l++) {
					if(i>k) break;
					if(i==k && j>l) continue;
					ch=0;
					for(int m=0;m<4;m++) {
						if(bomb[k][l+m]!=' ' && bomb[k][l+m]!='4') {
							ch=-1;
							break;
						}
					}
					if(ch!=-1) {
						check=0;
						for(int m=0;m<4;m++) {
							for(int n=0;n<4;n++) {
								if((i+m)==k && j==(l+n)) check=-1;
							}
							if(check==-1) break;
						}
						if(check!=-1) {
							for(int m=0;m<4;m++) {
								probability[i+m][j]++;
								probability[k][l+m]++;
							}
						}
					}
				}
			}
		}
	}
	for(int i=0;i<10;i++) {
		for(int j=0;j<11-4;j++) {
			ch=0;
			for(int m=0;m<4;m++) {
				if(bomb[i][j+m]!=' ' && bomb[i][j+m]!='4') {
					ch=-1;
					break;
				}
			}
			if(ch==-1) continue;
			for(int k=0;k<11-4;k++) {
				for(int l=0;l<10;l++) {
					if(i>k) break;
					if(i==k && j>l) continue;
					ch=0;
					for(int m=0;m<4;m++) {
						if(bomb[k+m][l]!=' ' && bomb[k+m][l]!='4') {
							ch=-1;
							break;
						}
					}
					if(ch!=-1) {
						check=0;
						for(int m=0;m<4;m++) {
							for(int n=0;n<4;n++) {
								if(i==(k+n) && (j+m)==l) check=-1;
							}
							if(check==-1) break;
						}
						if(check!=-1) {
							for(int m=0;m<4;m++) {
								probability[i][j+m]++;
								probability[k+m][l]++;
							}
						}
					}
				}
			}
			for(int k=0;k<10;k++) {
				for(int l=0;l<11-4;l++) {
					if(i>k) break;
					if(i==k && j>l) continue;
					ch=0;
					for(int m=0;m<4;m++) {
						if(bomb[k][l+m]!=' ' && bomb[k][l+m]!='4') {
							ch=-1;
							break;
						}
					}
					if(ch!=-1) {
						check=0;
						for(int m=0;m<4;m++) {
							for(int n=0;n<4;n++) {
								if(i==k && (j+m)==(l+n)) check=-1;
							}
							if(check==-1) break;
						}
						if(check!=-1) {
							for(int m=0;m<4;m++) {
								probability[i][j+m]++;
								probability[k][l+m]++;
							}
						}
					}
				}
			}
		}
	}
}

void find_3(char **bomb, int probability[][10]) {
	int ch, check;

	for(int i=0;i<11-3;i++) {
		for(int j=0;j<10;j++) {
			ch=0;
			for(int p=0;p<3;p++) {
				if(bomb[i+p][j]!=' ' && bomb[i+p][j]!='3') {
					ch=-1;
					break;
				}
			}
			if(ch==-1) continue;
			for(int k=0;k<11-3;k++) {
				for(int l=0;l<10;l++) {
					if(i>k) break;
					if(i==k && j>l) continue;
					ch=0;
					for(int p=0;p<3;p++) {
						if(bomb[k+p][l]!=' ' && bomb[k+p][l]!='3') {
							ch=-1;
							break;
						}
					}
					if(ch==-1) continue;
					for(int m=0;m<11-3;m++) {
						for(int n=0;n<10;n++) {
							if(k>m) break;
							if(k==m && l>n) continue;
							ch=0;
							for(int p=0;p<3;p++) {
								if(bomb[m+p][n]!=' ' && bomb[m+p][n]!='3') {
									ch=-1;
									break;
								}
							}
							if(ch!=-1) {
								check=0;
								for(int p=0;p<3;p++) {
									for(int q=0;q<3;q++) {
										for(int r=0;r<3;r++) {
											if(((i+p)==(k+q) && j==l) || ((i+p)==(m+r) && j==n) || ((k+q)==(m+r) && l==n)) check=-1;
										}
										if(check==-1) break;
									}
									if(check==-1) break;
								}
								if(check!=-1) {
									for(int p=0;p<3;p++) {
										probability[i+p][j]++;
										probability[k+p][l]++;
										probability[m+p][n]++;
									}
								}
							}
						}
					}
					for(int m=0;m<10;m++) {
						for(int n=0;n<11-3;n++) {
							if(k>m) break;
							if(k==m && l>n) continue;
							ch=0;
							for(int p=0;p<3;p++) {
								if(bomb[m][n+p]!=' ' && bomb[m][n+p]!='3') {
									ch=-1;
									break;
								}
							}
							if(ch!=-1) {
								check=0;
								for(int p=0;p<3;p++) {
									for(int q=0;q<3;q++) {
										for(int r=0;r<3;r++) {
											if(((i+p)==(k+q) && j==l) || ((i+p)==m && j==(n+r)) || ((k+q)==m && l==(n+r))) check=-1;
										}
										if(check==-1) break;
									}
									if(check==-1) break;
								}
								if(check!=-1) {
									for(int p=0;p<3;p++) {
										probability[i+p][j]++;
										probability[k+p][l]++;
										probability[m][n+p]++;
									}
								}
							}
						}
					}
				}
			}
			for(int k=0;k<10;k++) {
				for(int l=0;l<11-3;l++) {
					if(i>k) break;
					if(i==k && j>l) continue;
					ch=0;
					for(int p=0;p<3;p++) {
						if(bomb[k][l+p]!=' ' && bomb[k][l+p]!='3') {
							ch=-1;
							break;
						}
					}
					if(ch==-1) continue;
					for(int m=0;m<11-3;m++) {
						for(int n=0;n<10;n++) {
							if(k>m) break;
							if(k==m && l>n) continue;
							ch=0;
							for(int p=0;p<3;p++) {
								if(bomb[m+p][n]!=' ' && bomb[m+p][n]!='3') {
									ch=-1;
									break;
								}
							}
							if(ch!=-1) {
								check=0;
								for(int p=0;p<3;p++) {
									for(int q=0;q<3;q++) {
										for(int r=0;r<3;r++) {
											if(((i+p)==k && j==(l+q)) || ((i+p)==(m+r) && j==n) || (k==(m+r) && (l+q)==n)) check=-1;
										}
										if(check==-1) break;
									}
									if(check==-1) break;
								}
								if(check!=-1) {
									for(int p=0;p<3;p++) {
										probability[i+p][j]++;
										probability[k][l+p]++;
										probability[m+p][n]++;
									}
								}
							}
						}
					}
					for(int m=0;m<10;m++) {
						for(int n=0;n<11-3;n++) {
							if(k>m) break;
							if(k==m && l>n) continue;
							ch=0;
							for(int p=0;p<3;p++) {
								if(bomb[m][n+p]!=' ' && bomb[m][n+p]!='3') {
									ch=-1;
									break;
								}
							}
							if(ch!=-1) {
								check=0;
								for(int p=0;p<3;p++) {
									for(int q=0;q<3;q++) {
										for(int r=0;r<3;r++) {
											if(((i+p)==k && j==(l+q)) || ((i+p)==m && j==(n+r)) || (k==m && (l+q)==(n+r))) check=-1;
										}
										if(check==-1) break;
									}
									if(check==-1) break;
								}
								if(check!=-1) {
									for(int p=0;p<3;p++) {
										probability[i+p][j]++;
										probability[k][l+p]++;
										probability[m][n+p]++;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	for(int i=0;i<10;i++) {
		for(int j=0;j<11-3;j++) {
			ch=0;
			for(int p=0;p<3;p++) {
				if(bomb[i][j+p]!=' ' && bomb[i][j+p]!='3') {
					ch=-1;
					break;
				}
			}
			if(ch==-1) continue;
			for(int k=0;k<11-3;k++) {
				for(int l=0;l<10;l++) {
					if(i>k) break;
					if(i==k && j>l) continue;
					ch=0;
					for(int p=0;p<3;p++) {
						if(bomb[k+p][l]!=' ' && bomb[k+p][l]!='3') {
							ch=-1;
							break;
						}
					}
					if(ch==-1) continue;
					for(int m=0;m<11-3;m++) {
						for(int n=0;n<10;n++) {
							if(k>m) break;
							if(k==m && l>n) continue;
							ch=0;
							for(int p=0;p<3;p++) {
								if(bomb[m+p][n]!=' ' && bomb[m+p][n]!='3') {
									ch=-1;
									break;
								}
							}
							if(ch!=-1) {
								check=0;
								for(int p=0;p<3;p++) {
									for(int q=0;q<3;q++) {
										for(int r=0;r<3;r++) {
											if((i==(k+q) && (j+p)==l) || (i==(m+r) && (j+p)==n) || ((k+q)==(m+r) && l==n)) check=-1;
										}
										if(check==-1) break;
									}
									if(check==-1) break;
								}
								if(check!=-1) {
									for(int p=0;p<3;p++) {
										probability[i][j+p]++;
										probability[k+p][l]++;
										probability[m+p][n]++;
									}
								}
							}
						}
					}
					for(int m=0;m<10;m++) {
						for(int n=0;n<11-3;n++) {
							if(k>m) break;
							if(k==m && l>n) continue;
							ch=0;
							for(int p=0;p<3;p++) {
								if(bomb[m][n+p]!=' ' && bomb[m][n+p]!='3') {
									ch=-1;
									break;
								}
							}
							if(ch!=-1) {
								check=0;
								for(int p=0;p<3;p++) {
									for(int q=0;q<3;q++) {
										for(int r=0;r<3;r++) {
											if((i==(k+q) && (j+p)==l) || (i==m && (j+p)==(n+r)) || ((k+q)==m && l==(n+r))) check=-1;
										}
										if(check==-1) break;
									}
									if(check==-1) break;
								}
								if(check!=-1) {
									for(int p=0;p<3;p++) {
										probability[i][j+p]++;
										probability[k+p][l]++;
										probability[m][n+p]++;
									}
								}
							}
						}
					}
				}
			}
			for(int k=0;k<10;k++) {
				for(int l=0;l<11-3;l++) {
					if(i>k) break;
					if(i==k && j>l) continue;
					ch=0;
					for(int p=0;p<3;p++) {
						if(bomb[k][l+p]!=' ' && bomb[k][l+p]!='3') {
							ch=-1;
							break;
						}
					}
					if(ch==-1) continue;
					for(int m=0;m<11-3;m++) {
						for(int n=0;n<10;n++) {
							if(k>m) break;
							if(k==m && l>n) continue;
							ch=0;
							for(int p=0;p<3;p++) {
								if(bomb[m+p][n]!=' ' && bomb[m+p][n]!='3') {
									ch=-1;
									break;
								}
							}
							if(ch!=-1) {
								check=0;
								for(int p=0;p<3;p++) {
									for(int q=0;q<3;q++) {
										for(int r=0;r<3;r++) {
											if((i==k && (j+p)==(l+q)) || (i==(m+r) && (j+p)==n) || (k==(m+r) && (l+q)==n)) check=-1;
										}
										if(check==-1) break;
									}
									if(check==-1) break;
								}
								if(check!=-1) {
									for(int p=0;p<3;p++) {
										probability[i][j+p]++;
										probability[k][l+p]++;
										probability[m+p][n]++;
									}
								}
							}
						}
					}
					for(int m=0;m<10;m++) {
						for(int n=0;n<11-3;n++) {
							if(k>m) break;
							if(k==m && l>n) continue;
							ch=0;
							for(int p=0;p<3;p++) {
								if(bomb[m][n+p]!=' ' && bomb[m][n+p]!='3') {
									ch=-1;
									break;
								}
							}
							if(ch!=-1) {
								check=0;
								for(int p=0;p<3;p++) {
									for(int q=0;q<3;q++) {
										for(int r=0;r<3;r++) {
											if((i==k && (j+p)==(l+q)) || (i==m && (j+p)==(n+r)) || (k==m && (l+q)==(n+r))) check=-1;
										}
										if(check==-1) break;
									}
									if(check==-1) break;
								}
								if(check!=-1) {
									for(int p=0;p<3;p++) {
										probability[i][j+p]++;
										probability[k][l+p]++;
										probability[m][n+p]++;
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

void find_2(char **bomb, int x, int y) { //#1
	int ch=0;

	if((x>0 && x<9 && y>0 && y<9) && ((bomb[x-1][y]=='2' && (bomb[x+1][y]!=' ' && bomb[x+1][y]!='2') && (bomb[x][y+1]!=' ' && bomb[x][y+1]!='2') && (bomb[x][y-1]!=' ' && bomb[x][y-1]=='2')) || ((bomb[x-1][y]!=' ' && bomb[x-1][y]!='2') && bomb[x+1][y]=='2' && (bomb[x][y+1]!=' ' && bomb[x][y+1]!='2') && (bomb[x][y-1]!=' ' && bomb[x][y-1]!='2')) || ((bomb[x-1][y]!=' ' && bomb[x-1][y]!='2') && (bomb[x+1][y]!=' ' && bomb[x+1][y]!='2') && bomb[x][y+1]=='2' && (bomb[x][y-1]!=' ' && bomb[x][y-1]!='2')) || ((bomb[x-1][y]!=' ' && bomb[x-1][y]!='2') && (bomb[x+1][y]!=' ' && bomb[x+1][y]!='2') && (bomb[x][y+1]!=' ' && bomb[x][y+1]!='2') && bomb[x][y-1]=='2'))) ch=-1;
	else if(x==0) {
		if(y==0 && (((bomb[x+1][y]!=' ' && bomb[x+1][y]!='2') && bomb[x][y+1]=='2') || (bomb[x+1][y]=='2' && (bomb[x][y+1]!=' ' && bomb[x][y+1]!='2')))) ch=-1;
		else if(y==9 && (((bomb[x+1][y]!=' ' && bomb[x+1][y]!='2') && bomb[x][y-1]=='2') || (bomb[x+1][y]=='2' && (bomb[x][y-1]!=' ' && bomb[x][y-1]!='2')))) ch=-1;
		else if((bomb[x+1][y]=='2' && (bomb[x][y+1]!=' ' && bomb[x][y+1]!='2') && (bomb[x][y-1]!=' ' && bomb[x][y-1]!='2')) || ((bomb[x+1][y]!=' ' && bomb[x+1][y]!='2') && bomb[x][y+1]=='2' && (bomb[x][y-1]!=' ' && bomb[x][y-1]!='2')) || ((bomb[x+1][y]!=' ' && bomb[x+1][y]!='2') && (bomb[x][y+1]!=' ' && bomb[x][y+1]!='2') && bomb[x][y-1]=='2')) ch=-1;
	}
	else if(x==9) {
		if(y==0 && (((bomb[x-1][y]!=' ' && bomb[x-1][y]!='2') && bomb[x][y+1]=='2') || (bomb[x-1][y]=='2' && (bomb[x][y+1]!=' ' && bomb[x][y+1]!='2')))) ch=-1;
		else if(y==9 && (((bomb[x-1][y]!=' ' && bomb[x-1][y]!='2') && bomb[x][y-1]=='2') || (bomb[x-1][y]=='2' && (bomb[x][y-1]!=' ' && bomb[x][y-1]!='2')))) ch=-1;
		else if((bomb[x-1][y]=='2' && (bomb[x][y+1]!=' ' && bomb[x][y+1]!='2') && (bomb[x][y-1]!=' ' && bomb[x][y-1]!='2')) || ((bomb[x-1][y]!=' ' && bomb[x-1][y]!='2') && bomb[x][y+1]=='2' && (bomb[x][y-1]!=' ' && bomb[x][y-1]!='2')) || ((bomb[x-1][y]!=' ' && bomb[x-1][y]!='2') && (bomb[x][y+1]!=' ' && bomb[x][y+1]!='2') && bomb[x][y-1]=='2')) ch=-1;
	}
	else if(y==0 && ((bomb[x][y+1]=='2' && (bomb[x-1][y]!=' ' && bomb[x-1][y]!='2') && (bomb[x+1][y]!=' ' && bomb[x+1][y]!='2')) || ((bomb[x][y+1]!=' ' && bomb[x][y+1]!='2') && bomb[x-1][y]=='2' && (bomb[x+1][y]!=' ' && bomb[x+1][y]!='2')) || ((bomb[x][y+1]!=' ' && bomb[x][y+1]!='2') && (bomb[x-1][y]!=' ' && bomb[x-1][y]!='2') && bomb[x+1][y]=='2'))) ch=-1;
	else if(y==9 && ((bomb[x][y-1]=='2' && (bomb[x-1][y]!=' ' && bomb[x-1][y]!='2') && (bomb[x+1][y]!=' ' && bomb[x+1][y]!='2')) || ((bomb[x][y-1]!=' ' && bomb[x][y-1]!='2') && bomb[x-1][y]=='2' && (bomb[x+1][y]!=' ' && bomb[x+1][y]!='2')) || ((bomb[x][y-1]!=' ' && bomb[x][y-1]!='2') && (bomb[x-1][y]!=' ' && bomb[x-1][y]!='2') && bomb[x+1][y]=='2'))) ch=-1;
	if(ch==-1) {
		bomb[x][y]='X';
		if(x>0) bomb[x-1][y]='X';
		if(x<9) bomb[x+1][y]='X';
		if(y>0) bomb[x][y-1]='X';
		if(y<9) bomb[x][y+1]='X';
	}
}

void search_2(char **bomb, int x, int y) { //#2
	vector<int> tmp;
	int temp;

	tmp.clear();
	if(x>0 && bomb[x-1][y]=='2') tmp.push_back((x-1)*10+y);
	if(x<9 && bomb[x+1][y]=='2') tmp.push_back((x+1)*10+y);
	if(y>0 && bomb[x][y-1]=='2') tmp.push_back(x*10+y-1);
	if(y<9 && bomb[x][y+1]=='2') tmp.push_back(x*10+y+1);

	while(tmp.size()!=0) {
		temp=tmp.back();
		find_2(bomb, temp/10, temp%10);
		tmp.pop_back();
	}
}

int guess(char **bomb, int *ship_cnt) {
	int probability[10][10], max=0, coordinate;

	for(int i=0;i<10;i++) {
		for(int j=0;j<10;j++) {
			probability[i][j]=0;
		}
	}
	if(ship_cnt[6]!=0) find_6(bomb, probability);
	if(ship_cnt[4]!=0) find_4(bomb, probability);
	if(ship_cnt[3]!=0) find_3(bomb, probability);
	for(int i=0;i<10;i++) {
		for(int j=0;j<10;j++) {
			if(bomb[i][j]!=' ') probability[i][j]=0;
		}
	}
	for(int i=0;i<10;i++) {
		for(int j=0;j<10;j++) {
			if(probability[i][j]>max && bomb[i][j]==' ') {
				max=probability[i][j];
				coordinate=i*10+j;
			}
			if(probability[i][j]==max && bomb[i][j]==' ') {
				if(rand()%13<=6) coordinate=i*10+j;
			}
		}
	}

	return coordinate;
}

int find_aircraft(char **bomb) {
	int probability[10][10], max=0, coordinate, ch;

	for(int i=0;i<10;i++) {
		for(int j=0;j<10;j++) {
			probability[i][j]=0;
		}
	}
	for(int i=0;i<11-2;i++) {
		for(int j=0;j<10;j++) {
			ch=0;
			if((bomb[i][j]!=' ' && bomb[i][j]!='2') || (bomb[i+1][j]!=' ' && bomb[i+1][j]!='2')) ch=-1;
			if(ch!=-1) {
				probability[i][j]++;
				probability[i+1][j]++;
			}
		}
	}
	for(int i=0;i<10;i++) {
		for(int j=0;j<11-2;j++) {
			ch=0;
			if((bomb[i][j]!=' ' && bomb[i][j]!='2') || (bomb[i][j+1]!=' ' && bomb[i][j+1]!='2')) ch=-1;
			if(ch!=-1) {
				probability[i][j]++;
				probability[i][j+1]++;
			}
		}
	}
	for(int i=0;i<10;i++) {
		for(int j=0;j<10;j++) {
			if(bomb[i][j]=='2') {
				if(i>0) probability[i-1][j]*=2;
				if(i<9) probability[i+1][j]*=2;
				if(j>0) probability[i][j-1]*=2;
				if(j<9) probability[i][j+1]*=2;
			}
		}
	}
	for(int i=0;i<10;i++) {
		for(int j=0;j<10;j++) {
			if(bomb[i][j]!=' ') probability[i][j]=0;
		}
	}
	for(int i=0;i<10;i++) {
		for(int j=0;j<10;j++) {
			if(probability[i][j]>max && bomb[i][j]==' ') {
				max=probability[i][j];
				coordinate=i*10+j;
			}
		}
	}

	return coordinate;
}

int main(int argc, char **argv) {
	char **board, **bomb;
	int bomb_num, score=0, *ship_cnt, bomb_cnt=0, coordinate, x, y, temp, finish=0;
	vector<int> tmp;

	srand(time(NULL));
	bomb_num=atoi(argv[1]);
	board=input_file();
	bomb=(char **)malloc(sizeof(char *)*10);
	for(int i=0;i<10;i++) {
		bomb[i]=(char *)malloc(sizeof(char)*10);
	}
	ship_cnt=(int *)malloc(sizeof(int)*7);
	ship_cnt[2]=8;
	ship_cnt[3]=9;
	ship_cnt[4]=8;
	ship_cnt[6]=6;
	for(int i=0;i<10;i++) {
		for(int j=0;j<10;j++) {
			bomb[i][j]=' ';
		}
	}
	coordinate=guess(bomb, ship_cnt);
	while(!(ship_cnt[3]==0 && ship_cnt[4]==0 && ship_cnt[6]==0)) {
		if(board[coordinate/10][coordinate%10]=='0') {
			x=coordinate/10;
			y=coordinate%10;
			bomb[x][y]='X';
			bomb_cnt++;
			//search for '2' around X (#3)
			tmp.clear();
			if(x>0 && bomb[x-1][y]=='2') tmp.push_back((x-1)*10+y);
			if(x<9 && bomb[x+1][y]=='2') tmp.push_back((x+1)*10+y);
			if(y>0 && bomb[x][y-1]=='2') tmp.push_back(x*10+y-1);
			if(y<9 && bomb[x][y+1]=='2') tmp.push_back(x*10+y+1);
			while(tmp.size()!=0) {
				temp=tmp.back();
				find_2(bomb, temp/10, temp%10);
				search_2(bomb, temp/10, temp%10);
				tmp.pop_back();
			}
		}
		else {
			x=coordinate/10;
			y=coordinate%10;
			bomb[x][y]=board[x][y];
			bomb_cnt++;
			score+=(board[x][y]-'0');
			ship_cnt[board[x][y]-'0']--;
			if(board[x][y]=='2') {
				find_2(bomb, x, y);
				search_2(bomb, x, y);
			}
		}
		if(bomb_num!=0 && bomb_cnt==bomb_num) {
			finish=-1;
			break;
		}
		coordinate=guess(bomb, ship_cnt);
	}
	coordinate=find_aircraft(bomb);
	while(ship_cnt[2]!=0 && finish!=-1) {
		if(board[coordinate/10][coordinate%10]=='0') {
			x=coordinate/10;
			y=coordinate%10;
			bomb[x][y]='X';
			bomb_cnt++;
			//search for '2' around X (#3)
			tmp.clear();
			if(x>0 && bomb[x-1][y]=='2') tmp.push_back((x-1)*10+y);
			if(x<9 && bomb[x+1][y]=='2') tmp.push_back((x+1)*10+y);
			if(y>0 && bomb[x][y-1]=='2') tmp.push_back(x*10+y-1);
			if(y<9 && bomb[x][y+1]=='2') tmp.push_back(x*10+y+1);
			while(tmp.size()!=0) {
				temp=tmp.back();
				find_2(bomb, temp/10, temp%10);
				search_2(bomb, temp/10, temp%10);
				tmp.pop_back();
			}
		}
		else {
			x=coordinate/10;
			y=coordinate%10;
			bomb[x][y]=board[x][y];
			bomb_cnt++;
			score+=2;
			ship_cnt[2]--;
			find_2(bomb, x, y);
			search_2(bomb, x, y);
		}
		if(bomb_num!=0 && bomb_cnt==bomb_num) break;
		coordinate=find_aircraft(bomb);
	}

	cout << score << " " << bomb_cnt << endl;
	free(board);
	free(bomb);
	free(ship_cnt);

	return 0;
}
