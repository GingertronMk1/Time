function validateArtistForm() {
  var fields = ["newname"];
  console.log(fields);
  var i, l = fields.length;
  var field;
  var validated = 1;
  for (i = 0; i < l; i++) {
    var formElement = document.forms["artistform"][fields[i]];
    if(formElement.value == ""){
      //alert(fields[i] + " must be filled out");
      formElement.style.border = "1px solid red";
      formElement.placeholder = "You need to fill this in";
      validated = 0;
    }
  }
  if(validated){
    return true;
  } else {
    return false
  }
}

function validateAlbumForm() {
  var fields = ["newartist", "newname", "newprice", "newgenre", "newtrackno"];
  console.log(fields);
  var i, l = fields.length;
  var field;
  var validated = 1;
  for (i = 0; i < l; i++) {
    var formElement = document.forms["albumform"][fields[i]];
    if(formElement.value == ""){
      //alert(fields[i] + " must be filled out");
      formElement.style.border = "1px solid red";
      formElement.placeholder = "You need to fill this in";
      validated = 0
    }
  }
  if(validated){
    return true;
  } else {
    return false
  }
}

function validateTrackForm() {
  var fields = ["newalbum", "newname", "newlength"];
  console.log(fields);
  var i, l = fields.length;
  var field;
  var validated = 1;
  for (i = 0; i < l; i++) {
    var formElement = document.forms["trackform"][fields[i]];
    if(formElement.value == ""){
      //alert(fields[i] + " must be filled out");
      formElement.style.border = "1px solid red";
      formElement.placeholder = "You need to fill this in";
      validated = 0
    }
  }
  if(validated){
    return true;
  } else {
    return false
  }
}
