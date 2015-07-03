byte get_bcd()
   {
      char first, second;

      do
         {
            first=getc();
         } while ((first<'0') || (first>'9'));
      putc(first);

      do
         {
            second=getc();
         } while ((second<'0') || (second>'9') && (second!='\r'));
      putc(second);

      if (second=='\r')
         return (first-'0');
      else
         return (((first-'0') << 4) | (second-'0'));
   }


void display_bcd (byte n )
   {
      putc ( n/16+'0' );
      putc ( n%16+'0' );

   }
