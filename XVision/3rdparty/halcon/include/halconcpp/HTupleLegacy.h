  // This file includes wrapper signatures compatible
  // with HTuple in HALCON 10.0 or older

  // Special signatures
  Hlong  Num() const {return Length();}
  void   Reset() {Clear();}
  HTuple Getenv() {return TupleEnvironment();}
  HTuple ToString(const HTuple& pattern) const {return TupleString(pattern[0].S());}
  HTuple Subset(const HTuple& index) const {return TupleSelect(index);}
  

  // General shortened operator names without Tuple prefix
  HTuple Substring(const HTuple& Index1, const HTuple& Index2) const {return TupleSubstr(Index1,Index2);}
  HTuple HistoRange(const HTuple& Min, const HTuple& Max, const HTuple& NumBins, HTuple* BinSize) const {return TupleHistoRange(Min, Max, NumBins, BinSize);}
  HTuple RegexpSelect(const HTuple& Expression) const {return TupleRegexpSelect(Expression);}
  HTuple RegexpTest(const HTuple& Expression) const {return TupleRegexpTest(Expression);}
  HTuple RegexpReplace(const HTuple& Expression, const HTuple& Replace) const {return TupleRegexpReplace(Expression, Replace);}
  HTuple RegexpMatch(const HTuple& Expression) const {return TupleRegexpMatch(Expression);}
  HTuple Rand() {return TupleRand(*this);}
  HTuple Sgn() const {return TupleSgn();}
  HTuple Max2(const HTuple& T2) const {return TupleMax2(T2);}
  HTuple Min2(const HTuple& T2) const {return TupleMin2(T2);}
  HTuple Max() const {return TupleMax();}
  HTuple Min() const {return TupleMin();}
  HTuple Cumul() const {return TupleCumul();}
  HTuple SelectRank(const HTuple& RankIndex) const {return TupleSelectRank(RankIndex);}
  HTuple Median() const {return TupleMedian();}
  HTuple Sum() const {return TupleSum();}
  HTuple Mean() const {return TupleMean();}
  HTuple Deviation() const {return TupleDeviation();}
  HTuple Uniq() const {return TupleUniq();}
  HTuple Find(const HTuple& T2) const {return TupleFind(T2);}
  HTuple SortIndex() const {return TupleSortIndex();}
  HTuple Sort() const {return TupleSort();}
  HTuple Inverse() const {return TupleInverse();}
  HTuple Concat(const HTuple& T2) const {return TupleConcat(T2);}
  HTuple SelectRange(const HTuple& Leftindex, const HTuple& Rightindex) const {return TupleSelectRange(Leftindex, Rightindex);}
  HTuple LastN(const HTuple& Index) const {return TupleLastN(Index);}
  HTuple FirstN(const HTuple& Index) const {return TupleFirstN(Index);}
  HTuple Remove(const HTuple& Index) const {return TupleRemove(Index);}
  HTuple Select(const HTuple& Index) const {return TupleSelect(Index);}
  HTuple StrBitSelect(const HTuple& Index) const {return TupleStrBitSelect(Index);}
  HTuple Environment() const {return TupleEnvironment();}
  HTuple Split(const HTuple& T2) const {return TupleSplit(T2);}
  HTuple StrLastN(const HTuple& T2) const {return TupleStrLastN(T2);}
  HTuple StrFirstN(const HTuple& T2) const {return TupleStrFirstN(T2);}
  HTuple Strrchr(const HTuple& T2) const {return TupleStrrchr(T2);}
  HTuple Strchr(const HTuple& T2) const {return TupleStrchr(T2);}
  HTuple Strrstr(const HTuple& T2) const {return TupleStrrstr(T2);}
  HTuple Strstr(const HTuple& T2) const {return TupleStrstr(T2);}
  HTuple Strlen() const {return TupleStrlen();}
  HTuple LessEqual(const HTuple& T2) const {return TupleLessEqual(T2);}
  HTuple Less(const HTuple& T2) const {return TupleLess(T2);}
  HTuple GreaterEqual(const HTuple& T2) const {return TupleGreaterEqual(T2);}
  HTuple Greater(const HTuple& T2) const {return TupleGreater(T2);}
  HTuple NotEqual(const HTuple& T2) const {return TupleNotEqual(T2);}
  HTuple Equal(const HTuple& T2) const {return TupleEqual(T2);}
  HTuple Not() const {return TupleNot();}
  HTuple Xor(const HTuple& T2) const {return TupleXor(T2);}
  HTuple Or(const HTuple& T2) const {return TupleOr(T2);}
  HTuple And(const HTuple& T2) const {return TupleAnd(T2);}
  HTuple Bnot() const {return TupleBnot();}
  HTuple Bxor(const HTuple& T2) const {return TupleBxor(T2);}
  HTuple Bor(const HTuple& T2) const {return TupleBor(T2);}
  HTuple Band(const HTuple& T2) const {return TupleBand(T2);}
  HTuple Rsh(const HTuple& Shift) const {return TupleRsh(Shift);}
  HTuple Lsh(const HTuple& Shift) const {return TupleLsh(Shift);}
  HTuple Chrt() const {return TupleChrt();}
  HTuple Ords() const {return TupleOrds();}
  HTuple Chr() const {return TupleChr();}
  HTuple Ord() const {return TupleOrd();}
  HTuple String(const HTuple& Format) const {return TupleString(Format);}
  HTuple IsNumber() const {return TupleIsNumber();}
  HTuple Number() const {return TupleNumber();}
  HTuple Round() const {return TupleRound();}
  HTuple Int() const {return TupleInt();}
  HTuple Real() const {return TupleReal();}
  HTuple Ldexp(const HTuple& T2) const {return TupleLdexp(T2);}
  HTuple Fmod(const HTuple& T2) const {return TupleFmod(T2);}
  HTuple Mod(const HTuple& T2) const {return TupleMod(T2);}
  HTuple Ceil() const {return TupleCeil();}
  HTuple Floor() const {return TupleFloor();}
  HTuple Pow(const HTuple& T2) const {return TuplePow(T2);}
  HTuple Log10() const {return TupleLog10();}
  HTuple Log() const {return TupleLog();}
  HTuple Exp() const {return TupleExp();}
  HTuple Tanh() const {return TupleTanh();}
  HTuple Cosh() const {return TupleCosh();}
  HTuple Sinh() const {return TupleSinh();}
  HTuple Rad() const {return TupleRad();}
  HTuple Deg() const {return TupleDeg();}
  HTuple Atan2(const HTuple& X) const {return TupleAtan2(X);}
  HTuple Atan() const {return TupleAtan();}
  HTuple Acos() const {return TupleAcos();}
  HTuple Asin() const {return TupleAsin();}
  HTuple Tan() const {return TupleTan();}
  HTuple Cos() const {return TupleCos();}
  HTuple Sin() const {return TupleSin();}
  HTuple Fabs() const {return TupleFabs();}
  HTuple Sqrt() const {return TupleSqrt();}
  HTuple Abs() const {return TupleAbs();}
  HTuple Neg() const {return TupleNeg();}
  HTuple Div(const HTuple& Q2) const {return TupleDiv(Q2);}
  HTuple Mult(const HTuple& P2) const {return TupleMult(P2);}
  HTuple Sub(const HTuple& D2) const {return TupleSub(D2);}
  HTuple Add(const HTuple& S2) const {return TupleAdd(S2);}

  // Legacy operator overloads

  HTuple operator () (Hlong min, Hlong max) const {return TupleSelectRange(min,max);}
  HTuple operator () (const HTuple &min, const HTuple &max) const {return TupleSelectRange(min,max);}
