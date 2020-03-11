#// SNIPPET BEGIN src001

document.title

#// SNIPPET END



// var uri = "https://animeflv.net/anime/5512/tate-no-yuusha-no-nariagari";
var uri = "https://skythewood.blogspot.com/p/altina-sword-princess.html";

var tab = browser.newTab();



function hwp_main(status)
{
    console.log("load end: "+status);
    console.log("web title: "+tab.evaluate(ratel.snippet("src001")));
    ratel.exit();
}


console.log("hola mundo from script");
console.log("target: "+uri);
// tab.navigationLocked = true;
tab.open(uri,hwp_main);


/*
 * 
 * 
var obj = { number: 2, text: "hola mundo" }
console.log(obj)
console.log("obj: "+obj);
console.log("obj: ",obj);

console.log(ratel.snippet("src001"));

tab.window.open();
tab.onNavigationRequested = function(url)
{
    console.log("nav.url: "+url);
}

console.log("uri: "+uri_target);

tab.open(uri_target,function(status){
    console.log( JSON.stringify(tab,null,2) );
    setTimeout(5000,function(){
        console.log("set page null");
        console.log( JSON.stringify(tab,null,2) );
        console.log("tab.window.page = null");
        console.log( JSON.stringify(tab,null,4) );
    });
});

setTimeout(1500,ratel.exit);

*/


