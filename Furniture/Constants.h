

#define kBookPageSize 20

#define kPhoneWidth 320
#define kPhoneHeight 480
#define kPadWidth 768
#define kPadHeight 1024

typedef enum  {
    OrderTypeHot = 0,//人气火爆
    OrderTypeNew = 1//最近更新
}OrderType;

typedef enum {
    BookStateAll=0,//全部
    BookStateContinue = 1,//连载中
    BookStateFinished = 2//已完结
}BookState;

typedef enum{
    SectionNotDownload=0,//未下载
    SectionDownloading=1,//正在下载
    SectionDownloaded=2,//下载完成
    SectionWatting=3,//地址获取中
    SectionPause=4,//暂停中
    SectionNew=5,//新增下载
    SectionContinue=6,//继续下载
    SectionCancel=7,//取消下载
} SectionDownloadState;

typedef enum{
    ClientiPhone4=1,
    ClientiPod1G=2,
    ClientiPhone4S=3,
    ClientiPad1=4,
    ClientiPhone5=5,
    ClientiPhone1G=6,
    ClientiPhone2G=7,
    ClientiPhone3GS=8,
    ClientiPod2G=9,
    ClientiPod3G=10,
    ClientiPod4G=11,
    ClientiPad2=12,
    ClientiPad3=13,
    
} ClientType;//客户端机器型号


#define kDownloadingPath [[[FileHelper sharedInstance] getDocumentPath] stringByAppendingPathComponent:@"Downloading"]
#define kDownloadedPath [[[FileHelper sharedInstance] getDocumentPath] stringByAppendingPathComponent:@"Downloaded"]
#define kSectionConfigName @"SectionConfig"
#define kBookConfigName @"BookConfig"//图书下载完成时在每本书籍的文件夹根目录下生成
#define kDefaultDownloadFolder @"默认文件夹"//默认图书下载的文件夹名称


#define APPDELEGATE ((AppDelegate *)[[UIApplication sharedApplication] delegate])



#define kAppDownloadURL @"http://itunes.apple.com/cn/app/id580349899?mt=8#"

#define kCellNameColor [UIColor colorWithRed:52/255.0 green:58/255.0 blue:73/255.0 alpha:1.0f]