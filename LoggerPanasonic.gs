//-----------------------------------------------
//Originally published by Mogsdad@Stackoverflow
//Modified for jarkomdityaz.appspot.com
///
///Modified by PDAControl Jhon Valencia   -- ESP8266 Direct connection
///http://pdacontrolenglish.blogspot.com.co
///https://youtu.be/5f7wCeD4gB4
//-----------------------------------------------
/*

GET request query:


*/


/* Using spreadsheet API */

var timezone = "GMT-5";
//var timestamp_format = "MM-dd-yyyy"; // Timestamp Format. 
var timestamp_format = "yyyy-MM-dd HH:mm:ss";
//var formattedDate = Utilities.formatDate(time, "GMT", "MM-dd-yyyy HH:mm:ss");


function doPost(e) {
  var val = e.parameter.value;
  
  if (e.parameter.value !== undefined){
    var range = sheet.getRange('A2');
    range.setValue(val);
  }
}



function doGet(e) { 
  Logger.log( JSON.stringify(e) );  // view parameters

  var result = 'Ok'; // assume success

  if (e.parameter == undefined) {
    result = 'No Parameters';
  }
  else {
    var id = '####################################'; // Spreadsheet ID  from url Spreadsheet
    var sheet = SpreadsheetApp.openById(id).getActiveSheet();
    var newRow = sheet.getLastRow() + 1;
    var rowData = [];
    //var waktu = new Date();
 //   rowData[0] = new Date(); // Timestamp in column A
    
    var date = Utilities.formatDate(new Date(), timezone, timestamp_format);
    
    
    for (var param in e.parameter) {
      Logger.log('In for loop, param='+param);
      var value = stripQuotes(e.parameter[param]);
      //Logger.log(param + ':' + e.parameter[param]);
      switch (param) {
        case 'now': //Parameter   now  Current Status
           var range = sheet.getRange('G2'); ///// ESTADO ACTUAL ESP
           range.setValue(value); 
           rowData[0] = ''  ;
           break;
        case 'value': //Parameter   values      
          rowData[1] = value; //Value in column B
          rowData[0] =  date;          
          var range = sheet.getRange('D2');   ////inserta valor actual
          range.setValue(value);          
          var range = sheet.getRange('E2');  // insterta datetime
          range.setValue(date);              // insterta datetime      
          
          break;
       case 'column_C':  no used  - no utilizado
           rowData[2] = value;
           break;
       case 'read':
           return ContentService.createTextOutput(sheet.getRange('F2').getValue());   /// envia parametro a ESP8266  -- send parameter to ESP8266
           break;  
       default:
          result = "unsupported parameter";
      }
    }
    Logger.log(JSON.stringify(rowData));

    // Write new row below
    var newRange = sheet.getRange(newRow, 1, 1, rowData.length);
    newRange.setValues([rowData]);
  }

  // Return result of operation
  return ContentService.createTextOutput(result);
}

/**
* Remove leading and trailing single or double quotes
*/
function stripQuotes( value ) {
  return value.replace(/^["']|['"]$/g, "");
}