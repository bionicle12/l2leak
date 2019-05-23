// +----------------------------------------------------------------------+
// | Logger                                                               |
// +----------------------------------------------------------------------+
// | Singleton Pattern                                                    |
// +----------------------------------------------------------------------+
// | Author: Kim Soo Min <soomin@soomin.net>                              |
// +----------------------------------------------------------------------+

#ifndef _SOOMIN_HEADER_LOG
#define _SOOMIN_HEADER_LOG

enum Error
{
    eNoError = 0,
    eNonExistingAccount = 1,
    eIncorrectPassword = 2,
    eShouldChangePassword = 3,
    eShouldChangeQuiz = 4,
    eDuplicateLogin = 5,
    eBlockedAccount = 6,
    eNotGMAccount = 7,
    eUnexpectedGame = 8,
    eUnmatchedTail = 9,
    eWorldDown = 10,
    eNonExistingChar = 11,
    eBlockedChar = 12,
    eUnexpectedWorld = 13,
    eGMAlreadyLeaved = 14,
    eUnexpectedPetitionGrade = 15,
    eUnexpectedPetitionId = 16,
    eAlreadyCheckedOut = 17,
    eCheckInFirst = 18,
    eNoRightToAccess = 19,
    eCheckOutFirst = 20,
    eMailUnavailable = 21,
    eUnexpectedGMGrade = 22,
    eNoMarkForDeletion = 23,
    eWorldAlreadyConnected = 24,
    eObsoleteBuildNumber = 25,
    eCharAlreadySubmitted = 26,
    eInvalidState = 27,
    eDatabaseFail = 28,
    eNetworkFail = 29,
    eInternalServerFail = 30,
    eNoWorld = 31,
    eLoginFirst = 32,
    eEnterWorldFirst = 33,
    eGMAlreadyEntered = 34,
    eUnmatchedSession = 35,
    eUnexpectedCategory = 36,
    eUnexpectedOpCode = 37,
    eAlreadyChatStarted = 38,
    eAlreadyChatEnded = 39,
    eShouldChangeSSN = 40,
    eExpiredAccount = 41,
    eTooManyPetitions = 42,
    eCharNoPetition = 43
};

class Log
{
public:
	void AttachFile( const char* filename );
	void AttachEditCtrl( CEdit* pControl );

	void DetachFile();
	void DetachEditCtrl();

	void Write( char* fmt, ... );
	void WriteLn( char* fmt, ... );
	void WriteError( BYTE error_code );

	static Log* GetInstance();
	void Close();

	virtual ~Log();

protected:
	Log();
	void Add( LPCSTR str );

	static CString m_filename;
	CEdit* m_pEdit;
	CRITICAL_SECTION m_csLock;

private:
	static Log* m_instance;
};

#endif