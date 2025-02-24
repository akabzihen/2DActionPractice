#pragma once
class StageDataBase {
public:
	enum class MapChip : int {
		NONE = -1,

		Blank = 0,
		Square,
		RightUphill,
		RightDownhill,
		RighthandDownCelling,
		RighthandUpCelling,
		OnlyJudgingUpsideDownsideCelling,
		SlopeAssistance,
		Goal,

		MAX
	};

public:
	StageDataBase() {};
	virtual ~StageDataBase() {};

	virtual MapChip GetMapData(int x, int y) = 0;

	virtual int GetStageDataId() = 0;
};