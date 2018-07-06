package de.twometer.mycraft;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

public class LoginActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);

        final TextView usernameInput = findViewById(R.id.username_input);
        final TextView serverInput = findViewById(R.id.server_input);

        findViewById(R.id.connect_button).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String username = usernameInput.getText().toString();
                String server = serverInput.getText().toString();

                Intent intent = new Intent(LoginActivity.this, GameActivity.class);
                intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_CLEAR_TASK);
                intent.putExtra(GameActivity.EXTRA_USERNAME, username);
                intent.putExtra(GameActivity.EXTRA_SERVER, server);
                startActivity(intent);
            }
        });

    }
}
