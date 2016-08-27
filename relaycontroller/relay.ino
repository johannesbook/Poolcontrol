void relay (int i, bool state) {
  switch (i) {
    case 1:
      digitalWrite(3,!state);
      break;
  }
}

