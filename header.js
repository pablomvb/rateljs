var uri_target = "https://animeflv.net/anime/5512/tate-no-yuusha-no-nariagari";

### BEGIN SNIPPET jstest
console.log("hola mundo");
### END

var tab = Browser.newTab();
tab.window.open();

tab.onLoadFinished = function (status)
{
    var title = tab.evaluate("document.title + ' from browser';",null);
    console.log("<tab>.title: "+title);
    
    console.log("fn:m_toc_handle_page","process page > get toc");
    
    if( status !== true )
    {
        console.log("fn:m_toc_handle_page","error load page to process");
        JSBrowser.exit(1);
        return;
    }
    
    console.log(tab.url);
    
    var anime_info = tab.evaluate("JSON.stringify(anime_info);");
    var chapters = tab.evaluate("JSON.stringify(episodes.reverse());");
    
    console.log(anime_info);
    console.log(chapters);
    
    console.log("fn:m_toc_handle_page","finish");
    //JSBrowser.exit();
}

setTimeout(1000,function(){
    console.log("open page");
    tab.open(uri_target);
});

//setTimeout(5000,function(){ tab.window.close(); });

// System.args.slice(1)
// rsync -rlptD --progress YST-157.mp4 /run/media/pablo/otherdata/81aidem/mov.mp4
