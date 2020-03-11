(function(){
    var c_log = console.log;
    console.log = function()
    {
        c_log( JSON.stringify( arguments ) );
    }
})()


function vreturn(arg)
{
    if( typeof arg === 'object' ) return JSON.stringify(arg);

    return arg;
}
